/*----------------------------------------------------------------------------
 * Name:        led.cpp
 * Description: Data structure to manage the LEDs
 * Note(s):
 *
 *----------------------------------------------------------------------------*/

#include "led.h"

/*----------------------------------------------------------------------------
 Functions
 *----------------------------------------------------------------------------*/

led_t::led_t(int _pin, bool _active_high) {
  pin = _pin;
  active_high = _active_high;
  state = OFF;
  num_flashes = 1;
  flash_counter = 0;
  next_flash_transition = 0;
}

void led_t::set_flashes(int _num_flashes) {
  num_flashes = _num_flashes;
}

void led_t::set_state(int _state) {
  // Protect against spamming FLASH_ON or FLASH_OFF
  if ((state == FLASH_OFF || state == FLASH_ON) &&
      (_state == FLASH_OFF || _state == FLASH_ON)) {
    return;
  }
  else {
    state = static_cast<led_state_t>(_state);
  }
}

void led_t::update() {
  switch (state) {
    case SOLID:
      digitalWrite(pin, active_high);
      break;
    case FLASH_ON:
      digitalWrite(pin, active_high);
      if (millis() > next_flash_transition) {
        flash_counter++;
        if (flash_counter >= num_flashes) {
          flash_counter = 0;
          next_flash_transition = millis() + FLASH_WAIT_TIME;
        }
        else {
          next_flash_transition = millis() + FLASH_OFF_TIME;
        }
        state = FLASH_OFF;
      }
      break;
    case FLASH_OFF:
      digitalWrite(pin, !active_high);
      if (millis() > next_flash_transition) {
        state = FLASH_ON;
        next_flash_transition = millis() + FLASH_ON_TIME;
      }
      break;
    default:
      digitalWrite(pin, !active_high);
      break;
  }
}