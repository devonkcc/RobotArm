/*----------------------------------------------------------------------------
 * Name:        encoder.c
 * Description: Data structure to manage the encoder
 * Note(s):     Requires semaphores to be added if used with threading
 *
 *----------------------------------------------------------------------------*/

#include "encoder.h"

/*----------------------------------------------------------------------------
 Functions
 *----------------------------------------------------------------------------*/

encoder_t::encoder_t(int _ch_a, int _ch_b) {
  ch_a = _ch_a;
  ch_b = _ch_b;
  enable = false;
  counter = NULL;
}

void encoder_t::update_counter(float delta_counter) {
  float new_counter_value = counter->count + delta_counter;
  if (new_counter_value > counter->upper_limit) {
    if (counter->circular)
      counter->count = new_counter_value - counter->upper_limit;
    else
      counter->count = counter->upper_limit;
  }
  else if (new_counter_value < 0) {
    if (counter->circular)
      counter->count = new_counter_value + counter->upper_limit;
    else
      counter->count = 0;
  }
  else {
    counter->count = new_counter_value;
  }
}

void encoder_t::read() {
  // Check enable flag
  if (!enable)
    return;
  // Poll encoder
  bool curr_a = digitalRead(ch_a);
  bool curr_b = digitalRead(ch_b);
  unsigned int encoder_input = (prev_a<<3) | (prev_b<<2) | (curr_a<<1) | (curr_b);
  // Check for state transitions
  if (encoder_input == 0b0001 || encoder_input == 0b0111 ||
      encoder_input == 0b1000 || encoder_input == 0b1110) {
    update_counter(-1*counter->step_size);
  }
  else if (encoder_input == 0b0010 || encoder_input == 0b0100 ||
           encoder_input == 0b1011 || encoder_input == 0b1101) {
    update_counter(counter->step_size);
  }
  prev_a = curr_a;
  prev_b = curr_b;
}