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

#define TIME_FOR_BUTTON_HOLD 1000

typedef enum button_state {
  PRESS,
  RELEASE,
  HOLD
} button_state_t;

class button_t {
  private:
    int pin;
    button_state_t state;
    unsigned long time_stamp;
    bool click_flag;
    bool hold_flag;
    bool active_low;
  public:
    button_t(int pin, bool active_low);
    void read();
    bool check_button_hold();
    bool check_button_click();
};

#endif __BUTTON__