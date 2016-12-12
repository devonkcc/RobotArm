/*----------------------------------------------------------------------------
* Name:        file_name.c
* Description: Short description
* Note(s):     Definitions and information
*
*----------------------------------------------------------------------------*/

#include "robot_arm.h"

int print_counter = 0;
long time_stamp = 0;
bool direction_bool = true;

void setup() {
  
  // Digital Inputs
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  pinMode(ENCODER_SW, INPUT); // active low
  pinMode(MODE, INPUT);
  
  // Digital Outpus
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
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
  base_angle.upper_limit = 360;
  
  // Initialize default encoder counter
  encoder.counter = counter_list[curr_counter];
  encoder.enable = true;
  
  // Initialize motors
  gripper.init();
  wrist.init();
  elbow.init();
  shoulder1.init();
  shoulder2.init();
  
  // Debug
  Serial.begin(9600);
}

void loop() {
//  encoder.read();
//  encoder_sw.read();
//  if(encoder_sw.check_button_click()) {
//    curr_counter = (curr_counter+1)%NUM_MOTORS;
//    encoder.counter = counter_list[curr_counter];
//    Serial.print("---------- Counter # -----------");
//    Serial.println(curr_counter+1);
//  }
  
//  gripper.move_abs(gripper_angle.val);
//  wrist.move_abs(wrist_angle.val);
//  elbow.move_abs(elbow_angle.val);
//  shoulder1.move_abs(shoulder_angle.val);
//  shoulder2.move_abs(shoulder_angle.val);
  
//  if ((millis()-time_stamp) > 10000) {
//    time_stamp = millis();
//    if (direction_bool)
//      base.move_abs(-45);
//    else
//      base.move_abs(45);
//    direction_bool = !direction_bool;
//  }
  
  base.move_abs(-45);
  delay(10000);
  base.move_abs(45);
  delay(10000);
  
  
//  
//  if (print_counter > 20000){
//    Serial.print("G:");
//    Serial.print(gripper_angle.val);
//    Serial.print(" W:");
//    Serial.print(wrist_angle.val);
//    Serial.print(" E:");
//    Serial.print(elbow_angle.val);
//    Serial.print(" S:");
//    Serial.print(shoulder_angle.val);
//    Serial.print(" B:");
//    Serial.println(base_angle.val);
//    print_counter = 0;
//  }
//  print_counter++;
}

/*
void loop() {
  //
  switch (robot_arm_state) {
    case REMOTE:
      statements
      break;
    case MANUAL:
      <#statements#>
      break;
    case RECORD:
      <#statements#>
      break;
    case PLAY:
      <#statements#>
      break;
    case PLAY_WAITING:
      <#statements#>
      break;
  }
  // State transition
  
}
*/

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