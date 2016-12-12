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
  float position;
  int enable_pin;
  int step_pin;
  int dir_pin;
  float speed;
  long eta;
public:
  stepper_motor_t(int _dir_pin, int _step_pin, int _en_pin, float _speed);
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

#endif __MOTORS__