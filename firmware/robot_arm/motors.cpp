/*----------------------------------------------------------------------------
 * Name:        file_name.c
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include "motors.h"
#define STEP 4

/*----------------------------------------------------------------------------
 Functions
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

/*----------------------------------------------------------------------------
 Timing Interrrupt for Stepper
 *----------------------------------------------------------------------------*/

unsigned long interrupt_period;
volatile unsigned long interrupt_counter;
volatile char overflowing;
volatile unsigned int tcnt2;
volatile unsigned int step_counter;

void setup_interrupt(unsigned long _interrupt_period) {
  float prescaler = 0.0;
  TIMSK2 &= ~(1<<TOIE2);
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
  ASSR &= ~(1<<AS2);
  TIMSK2 &= ~(1<<OCIE2A);
  
  // prescaler set to 64
  TCCR2B |= (1<<CS22);
  TCCR2B &= ~((1<<CS21) | (1<<CS20));
  prescaler = 64.0;
  
  tcnt2 = 256 - (int)((float)F_CPU * 0.001 / prescaler);
  
  interrupt_period = _interrupt_period;
}

void start_stepper() {
  interrupt_counter = 0;
  overflowing = 0;
  TCNT2 = tcnt2;
  TIMSK2 |= (1<<TOIE2);
}

void stop_stepper() {
  TIMSK2 &= ~(1<<TOIE2);
}

void overflow() {
  interrupt_counter += 1;
  
  if (interrupt_counter >= interrupt_period && !overflowing) {
    overflowing = 1;
    interrupt_counter = 0;
    // Toggle STEP line
    digitalWrite(STEP, LOW);
    delayMicroseconds(10);
    digitalWrite(STEP, HIGH);
    // Decrement counter
    step_counter--;
    overflowing = 0;
  }
  
  if (step_counter <= 0) {
    stop_stepper();
    digitalWrite(STEP, HIGH);
  }
}

ISR(TIMER2_OVF_vect) {
  TCNT2 = tcnt2;
  overflow();
}



stepper_motor_t::stepper_motor_t(int _dir_pin, int _step_pin, int _enable_pin,
                                 float _speed, float _step_size) {
  dir_pin = _dir_pin;
  step_pin = _step_pin;
  enable_pin = _enable_pin;
  speed = _speed;
  step_size = _step_size;
  position = 0;
}

long stepper_motor_t::move_abs(float _position) {
  int delta_steps = int((position-_position)/step_size);
  // Speed
  interrupt_period = (1000000/speed)*(360/200);
  setup_interrupt(interrupt_period);
  // Set direction
  if (delta_steps >= 0)
    digitalWrite(dir_pin, HIGH);
  else
    digitalWrite(dir_pin, LOW);
  step_counter = abs(delta_steps);
  eta = millis() + interrupt_period*step_counter;
  position = _position;
  digitalWrite(enable_pin, LOW);
  start_stepper();
  return eta;
}

