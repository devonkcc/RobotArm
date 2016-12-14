/*----------------------------------------------------------------------------
 * Name:        button.cpp
 * Description: Data structure to manage button style inputs
 * Note(s):     Requires semaphores to be added if used with threading
 *
 *----------------------------------------------------------------------------*/

#include "button.h"

/*----------------------------------------------------------------------------
 Functions
 *----------------------------------------------------------------------------*/

button_t::button_t(int _pin, bool _active_low) {
  pin = _pin;
  state = RELEASE;
  time_stamp = 0;
  click_flag = false;
  hold_flag = false;
  active_low = _active_low;
}

void button_t::read() {
  switch (state) {
    case RELEASE:
      // Check for button pressed
      if (digitalRead(pin)^(active_low)) { // XOR w/ active_low flg
        time_stamp = millis();
        state = PRESS;
      }
      break;
    case PRESS:
      // Check for hold timout
      if (millis()-(time_stamp) > TIME_FOR_BUTTON_HOLD) {
        hold_flag = true;
        state = HOLD;
      }
      // Check for regular button release (click)
      else if (!(digitalRead(pin)^(active_low))) { // XNOR w/ active_low flg
        click_flag = true;
        state = RELEASE;
      }
      break;
    case HOLD:
      // Check for regular release
      if (!(digitalRead(pin)^(active_low))) { // XNOR w/ active_low
        state = RELEASE;
      }
      break;
  }
}

bool button_t::check_button_hold() {
  if (hold_flag) {
    hold_flag = false;
    return true;
  }
  return false;
}

bool button_t::check_button_click() {
  if (click_flag) {
    click_flag = false;
    return true;
  }
  return false;
}