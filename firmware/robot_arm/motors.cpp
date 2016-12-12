/*----------------------------------------------------------------------------
 * Name:        file_name.c
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include "motors.h"

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
