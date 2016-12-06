/*----------------------------------------------------------------------------
 * Name:        button.c
 * Description: Data structure to manage button style inputs
 * Note(s):     Requires semaphores to be added if used with threading
 *
 *----------------------------------------------------------------------------*/

#include "button.h"

/*----------------------------------------------------------------------------
 Functions
 *----------------------------------------------------------------------------*/

void init_button(button_t* button, int pin, bool active_low) {
  button->pin = pin;
  button-> state = RELEASE;
  button->time_stamp = 0;
  button->click_flag = false;
  button->hold_flag = false;
  button->active_low = active_low;
}

void update_button(button_t* button) {
  switch (button->state) {
    case RELEASE:
      // Check for button pressed
      if (digitalRead(button->pin)^(button->active_low)) { // XOR w/ active_low flg
        button->time_stamp = millis();
        button->state = PRESS;
      }
      break;
    case PRESS:
      // Check for hold timout
      if (millis()-(button->time_stamp) > TIME_FOR_BUTTON_HOLD) {
        button->hold_flag = true;
        button->state = HOLD;
      }
      // Check for regular button release (click)
      else if (!(digitalRead(button->pin)^(button->active_low))) { // XNOR w/ active_low flg
        button->click_flag = true;
        button->state = RELEASE;
      }
      break;
    case HOLD:
      // Check for regular release
      if (!(digitalRead(button->pin)^(button->active_low))) { // XNOR w/ active_low
        button->state = RELEASE;
      }
      break;
  }
}

bool check_button_hold(button_t* button) {
  if (button->hold_flag) {
    button->hold_flag = false;
    return true;
  }
  return false;
}

bool check_button_click(button_t* button) {
  if (button->click_flag) {
    button->click_flag = false;
    return true;
  }
  return false;
}