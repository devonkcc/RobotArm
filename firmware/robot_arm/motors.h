/*----------------------------------------------------------------------------
 * Name:        motors.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include <Arduino.h>
#include <Servo.h>

#ifndef __MOTORS__
#define __MOTORS__

// Macros
#define STEP_INTERRUPT_ON TIMSK2 |= (1 << OCIE2A)
#define STEP_INTERRUPT_OFF TIMSK2 = 0

// Constants
#define SMALL_SERVO_SPEED 0.001
#define LARGE_SERVO_SPEED 0.001
#define BELT_GEAR_RATIO 0.1551724138
#define BASE_STEP_SIZE 0.2793103448
#define CLOCK_FREQUENCY 16000000 // 16MHz
#define STEPS_PER_REVOLUTION 200
#define TIMER2_PRESCALER 1024

// Stepper global variables
extern volatile bool timing_pin_state;
extern volatile int steps_remaining;
extern volatile bool stepper_dn;

class stepper_motor_t {
  private:
    float position; // degrees
    bool clockwise;
    int enable_pin;
    int step_pin;
    int dir_pin;
  public:
    float speed;
  private:
   int speed_to_ocr(float _speed); // _speed is in degrees/sec
  public:
    stepper_motor_t(int _dir_pin, int _step_pin, int _en_pin);
    void move_abs(float _position);
    void init_stepper_interrupt();
    void set_position(float _position);
};

class servo_motor_t {
private:
  Servo* servo_object;
  float position;
  float offset;
  int polarity;
  int pin;
  float speed; // degrees per millisecond
public:
  long eta;
  servo_motor_t(int _pin, Servo* _servo_object, int _polarity, float _offset,
                float _speed);
  long move_abs(float _position);
  void init();
};

#endif __MOTORS__