/*----------------------------------------------------------------------------
 * Name:        led.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <Arduino.h>

#ifndef __LED__
#define __LED__

#define FLASH_ON_TIME 200
#define FLASH_OFF_TIME 100
#define FLASH_WAIT_TIME 800

typedef enum led_state {
  OFF,
  SOLID,
  FLASH_ON,
  FLASH_OFF
} led_state_t;

class led_t {
  private:
    bool active_high; 
    int pin;
    led_state_t state;
    int num_flashes;
    int flash_counter;
    long next_flash_transition;
  public:
    led_t(int _pin, bool _active_high);
    void set_flashes(int _num_flashes);
    void set_state(int _state);
    void update();
  private:
};

#endif __LED__

