/*----------------------------------------------------------------------------
 * Name:        button.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

# include <stdbool.h>
#include <Arduino.h>

#ifndef __BUTTON__
#define __BUTTON__

#define TIME_FOR_BUTTON_HOLD 1500

typedef enum button_state {
  PRESS,
  RELEASE,
  HOLD
} button_state_t;

typedef struct {
  int pin;
  button_state_t state;
  unsigned long time_stamp;
  bool click_flag;
  bool hold_flag;
  bool active_low;
} button_t;

void init_button(button_t* button, int pin, bool active_low);
void update_button(button_t* button);
bool check_button_hold(button_t* button);
bool check_button_click(button_t* button);

#endif __BUTTON__