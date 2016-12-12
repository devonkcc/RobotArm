/*----------------------------------------------------------------------------
 * Name:        file_name.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include <Arduino.h>
#include <Servo.h>

#ifndef __MOTORS__
#define __MOTORS__

class stepper_motor_t {
private:
  float position; // degrees
  int enable_pin;
  int step_pin;
  int dir_pin; // degrees / second
  float speed;
  long eta;
  float step_size; // size of 1 step/microstep in degrees
public:
  stepper_motor_t(int _dir_pin, int _step_pin, int _en_pin, float _speed, float _step_stize);
  long move_abs(float _position);
};

class servo_motor_t {
private:
  Servo* servo_object;
  float position;
  float offset;
  int polarity;
  int pin;
  float speed; // degrees per millisecond
  long eta;
public:
  servo_motor_t(int _pin, Servo* _servo_object, int _polarity, float _offset,
                float _speed);
  long move_abs(float _position);
  void init();
};

/*----------------------------------------------------------------------------
 Timing Interrrupt for Stepper
 *----------------------------------------------------------------------------*/

extern unsigned long interrupt_period;
extern volatile unsigned long interrupt_counter;
extern volatile char overflowing;
extern volatile unsigned int tcnt2;

void setup_interrupt(unsigned long ms, void (*f)());
void start();
void stop();
void overflow();


#endif __MOTORS__