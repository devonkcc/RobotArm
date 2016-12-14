/*----------------------------------------------------------------------------
* Name:        file_name.c
* Description: Short description
* Note(s):     Definitions and information
*
*----------------------------------------------------------------------------*/

#include "robot_arm.h"

#define DEBUG

#ifdef DEBUG
int print_counter = 0;
#endif

void write_all_leds(int _state) {
  for (int i = 0; i < NUM_LEDS; i++) {
    (*led_list[i]).set_state(_state);
  }
}

void update_all_leds() {
  for (int i = 0; i < NUM_LEDS; i++) {
    (*led_list[i]).update();
  }
}

void write_all_axis_leds(int _state) {
  for (int i = 0; i < NUM_AXIS_LEDS; i++) {
    (*led_list[i]).set_state(_state);
    if (_state == FLASH_ON) {
      (*led_list[i]).set_flashes(1);
    }
  }
}

void setup() {
  
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  // Digital Inputs
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  pinMode(ENCODER_SW, INPUT); // active low
  pinMode(MODE, INPUT);
  
  // Digital Outpus
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(BASE_LED, OUTPUT);
  digitalWrite(A0, HIGH);
  pinMode(SHOULDER_PWM1, OUTPUT);
  pinMode(SHOULDER_PWM2, OUTPUT);
  pinMode(UPPER_LED, OUTPUT);
  pinMode(FOREARM_LED, OUTPUT);
  pinMode(ELBOW_PWM, OUTPUT);
  pinMode(WRIST_PWM, OUTPUT);
  pinMode(GRIPPER_PWM, OUTPUT);
  pinMode(GRIPPER_LED, OUTPUT);
  pinMode(STAT, OUTPUT);
  pinMode(HALL_SIGNAL, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  
  // Configure base counter
  base_angle.circular = true;
  base_angle.step_size = 1;
  base_angle.val = MAX_BASE_ROTATION/2;
  base_angle.upper_limit = MAX_BASE_ROTATION;

  // Configure startup servo positions
  gripper_angle.val = GRIPPER_STARTUP_POS;
  wrist_angle.val = WRIST_STARTUP_POS;
  elbow_angle.val = ELBOW_STARTUP_POS;
  shoulder_angle.val = SHOULDER_STARTUP_POS;
  
  // Initialize default encoder counter
  encoder.counter = counter_list[curr_counter];
  encoder.enable = true;
  
  // Initialize servo motors
  gripper.init();
  wrist.init();
  elbow.init();
  shoulder1.init();
  shoulder2.init();
  
  // Setup servo position
  base.set_position(MAX_BASE_ROTATION/2);
  
  // Enable stepper motor
  digitalWrite(ENABLE, LOW);
  
  // Initialize stat LED
  stat_led.set_state(FLASH_ON);
}

void loop() {
  // Collect data
  encoder.read();
  encoder_sw.read();
  mode.read();
  
  // Display state on stat LED
  stat_led.set_flashes(robot_arm_state+1);
  
  // State machine
  switch (robot_arm_state) {
    case REMOTE:
      encoder.enable = false;
      write_all_axis_leds(SOLID);
      break;
    case KNOB:
      encoder.enable = true;
      break;
    case RECORD:
      encoder.enable = true;
      break;
    case PLAY:
      write_all_axis_leds(SOLID);
      encoder.enable = false;
      break;
    case PLAY_WAITING:
      write_all_axis_leds(FLASH_ON);
      encoder.enable = false;
      break;
  }
  
  // State Transitions
  if (mode.check_button_click()) {
    robot_arm_state = static_cast<top_level_state_machine>
                      ((int(robot_arm_state)+1)%NUM_ARM_STATES);
  }
  
  // Check for swap axis
  if (encoder.enable && encoder_sw.check_button_click()) {
    curr_counter = (curr_counter+1)%NUM_MOTORS;
    encoder.counter = counter_list[curr_counter];
  }
  
  // Turn on axis LED
  if (encoder.enable) {
    // Set curr axis LED to solid except for gripper (counter 0)
    for (int i = 0; i < NUM_AXIS_LEDS; i++) {
      if (i != curr_counter && !(i == 1 && curr_counter == 0)) {
        (*led_list[i]).set_state(OFF);
      }
    }
    if (curr_counter == 0) {
      (*led_list[curr_counter]).set_flashes(2);
      (*led_list[curr_counter]).set_state(FLASH_ON);
    }
    else {
      (*led_list[curr_counter]).set_state(SOLID);
    }
  }
  
  // Write to motors
  gripper.move_abs(gripper_angle.val);
  wrist.move_abs(wrist_angle.val);
  elbow.move_abs(elbow_angle.val);
  shoulder1.move_abs(shoulder_angle.val);
  shoulder2.move_abs(shoulder_angle.val);
  if(stepper_dn)
    base.move_abs(base_angle.val);
  
  // Write to LEDs
  update_all_leds();
  
  // Debug
  #ifdef DEBUG
  if (print_counter > 20000){
    Serial.print("State:");
    Serial.print(robot_arm_state);
    Serial.print(" G:");
    Serial.print(gripper_angle.val);
    Serial.print(" W:");
    Serial.print(wrist_angle.val);
    Serial.print(" E:");
    Serial.print(elbow_angle.val);
    Serial.print(" S:");
    Serial.print(shoulder_angle.val);
    Serial.print(" B:");
    Serial.println(base_angle.val);
    print_counter = 0;
  }
  print_counter++;
  #endif
}

//mode.read();
//encoder_sw.read();
//encoder.read();
//
//if(mode.check_button_hold()) {
//  Serial.println("mode hold");
//}
//
//if(mode.check_button_click()) {
//  Serial.println("mode click");
//  encoder.enable = !encoder.enable;
//  if (encoder.enable)
//    Serial.println(" ------------ Encoder On ------------ ");
//    else
//      Serial.println(" ------------ Encoder Off ------------ ");
//      }
//
//if(encoder_sw.check_button_hold()) {
//  Serial.println("encoder hold");
//}
//
//if(encoder_sw.check_button_click()) {
//  if (!shoulder_active) {
//    Serial.println(" ------------ Shoulder Counter ------------ ");
//    encoder.counter = &shoulder_angle;
//  }
//  else {
//    Serial.println(" ------------ Base Counter ------------ ");
//    encoder.counter = &base_angle;
//  }
//  shoulder_active = !shoulder_active;
//}
//
//if (shoulder_active)
//Serial.println(shoulder_angle.count);
//else
//Serial.println(base_angle.count);