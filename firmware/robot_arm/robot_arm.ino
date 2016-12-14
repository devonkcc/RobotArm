/*----------------------------------------------------------------------------
* Name:        file_name.c
* Description: Short description
* Note(s):     Definitions and information
*
*----------------------------------------------------------------------------*/

#include "robot_arm.h"

#undef DEBUG

#ifdef DEBUG
int print_counter = 0;
#endif

void setup() {
  
  // Debug
  Serial.begin(9600);
  
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
}

void loop() {
  encoder.read();
  encoder_sw.read();
  if(encoder_sw.check_button_click()) {
    curr_counter = (curr_counter+1)%NUM_MOTORS;
    encoder.counter = counter_list[curr_counter];
  }
  
  gripper.move_abs(gripper_angle.val);
  wrist.move_abs(wrist_angle.val);
  elbow.move_abs(elbow_angle.val);
  shoulder1.move_abs(shoulder_angle.val);
  shoulder2.move_abs(shoulder_angle.val);
  if(stepper_dn)
    base.move_abs(base_angle.val);
  
#ifdef DEBUG
  if (print_counter > 20000){
    Serial.print("G:");
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