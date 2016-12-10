/*----------------------------------------------------------------------------
* Name:        file_name.c
* Description: Short description
* Note(s):     Definitions and information
*
*----------------------------------------------------------------------------*/

#include "robot_arm.h"

bool shoulder_active = true;

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
  pinMode(GRIP_PWM, OUTPUT);
  pinMode(GRIP_LED, OUTPUT);
  pinMode(STAT, OUTPUT);
  pinMode(HALL_SIGNAL, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  
  base_angle.circular = true;
  encoder.counter = &shoulder_angle;
  
  // Debug
  Serial.begin(9600);
}

void loop() {
  mode.read();
  encoder_sw.read();
  encoder.read();
  
  if(mode.check_button_hold()) {
    Serial.println("mode hold");
  }
  
  if(mode.check_button_click()) {
    Serial.println("mode click");
    encoder.enable = !encoder.enable;
    if (encoder.enable)
      Serial.println(" ------------ Encoder On ------------ ");
    else
      Serial.println(" ------------ Encoder Off ------------ ");
  }
  
  if(encoder_sw.check_button_hold()) {
    Serial.println("encoder hold");
  }
  
  if(encoder_sw.check_button_click()) {
    if (!shoulder_active) {
      Serial.println(" ------------ Shoulder Counter ------------ ");
      encoder.counter = &shoulder_angle;
    }
    else {
      Serial.println(" ------------ Base Counter ------------ ");
      encoder.counter = &base_angle;
    }
    shoulder_active = !shoulder_active;
  }
  
  if (shoulder_active)
    Serial.println(shoulder_angle.count);
  else
    Serial.println(base_angle.count);
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