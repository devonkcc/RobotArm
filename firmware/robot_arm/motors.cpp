/*----------------------------------------------------------------------------
 * Name:        motors.cpp
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include "motors.h"

#define INTERRUP_TOGGLE 4

// Stepper global variables
extern volatile bool timing_pin_state = false;
extern volatile int steps_remaining  = 0;
extern volatile bool stepper_dn = true;

/*----------------------------------------------------------------------------
 ISR
 *----------------------------------------------------------------------------*/

ISR(TIMER2_COMPA_vect){
  // Check if movement complete
  if (!steps_remaining) {
    // Turn interrupt off
    STEP_INTERRUPT_OFF;
    stepper_dn = true;
  }
  else {
    // Toggle the interrupt pin
    digitalWrite(INTERRUP_TOGGLE, LOW);
    steps_remaining--;
    digitalWrite(INTERRUP_TOGGLE, HIGH);
  }
}

/*----------------------------------------------------------------------------
 Stepper Class
 *----------------------------------------------------------------------------*/

stepper_motor_t::stepper_motor_t(int _dir_pin, int _step_pin, int _en_pin) {
  position = 0;
  clockwise = false;
  enable_pin = _en_pin;
  dir_pin = _dir_pin;
  step_pin = _step_pin;
  speed = 140;
//  low_on_done = enable_pin;
//  timing_pin = step_pin;
}

void stepper_motor_t::init_stepper_interrupt() {
  STEP_INTERRUPT_OFF;
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0; //initialize timer 2 counter value to 0
  OCR2A = speed_to_ocr(speed);
  TCCR2A |= (1 << WGM21); // turn on CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Set 1023 prescaler
}

void stepper_motor_t::set_position(float _position) {
  position = _position;
}

int stepper_motor_t::speed_to_ocr(float _speed) {
  return abs(int(BASE_STEP_SIZE*(CLOCK_FREQUENCY/TIMER2_PRESCALER)/_speed));
}

void stepper_motor_t::move_abs(float _position) {
  // Turn off timing interrupt
  init_stepper_interrupt();
  float delta_position = _position - position;
  position = _position;
  // Add delta stpes
  steps_remaining += int(delta_position/BASE_STEP_SIZE)*((clockwise)?-1:1);
  if (steps_remaining < 0) {
    //Reverse direction
    clockwise = !clockwise;
    digitalWrite(dir_pin, clockwise);
    steps_remaining *= -1;
  }
  // Set stepper_dn flag
  if (steps_remaining) {
    stepper_dn = false;
  }
  // Turn on timing interrupt
  STEP_INTERRUPT_ON;
}

/*----------------------------------------------------------------------------
 Servo Class
 *----------------------------------------------------------------------------*/

servo_motor_t::servo_motor_t(int _pin, Servo* _servo_object, int _polarity,
                             float _offset,  float _speed) {
  pin = _pin;
  servo_object = _servo_object;
  polarity = _polarity;
  offset = _offset;
  speed = _speed;
}

void servo_motor_t::init() {
  (*servo_object).attach(pin);
}

long servo_motor_t::move_abs(float _position) {
  (*servo_object).write((_position - offset)*polarity);
  eta = millis() + abs(position - _position)/speed;
  position = _position;
  return eta;
}

