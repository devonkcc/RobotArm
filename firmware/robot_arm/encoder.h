/*----------------------------------------------------------------------------
 * Name:        encoder.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <Arduino.h>

#ifndef __ENCODER__
#define __ENCODER__

typedef struct {
  bool circular = false;
  float count = 0;
  float step_size = 4.5;
  float upper_limit = 360.0;
} counter_t;

class encoder_t {
  public:
    counter_t* counter;
    bool enable;
  private:
    int ch_a;
    int ch_b;
    bool prev_a;
    bool prev_b;
  public:
    encoder_t(int ch_a, int ch_b);
    void read();
  private:
    void update_counter(float delta_counter);
};

#endif __ENCODER__