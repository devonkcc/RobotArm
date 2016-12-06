/*----------------------------------------------------------------------------
* Name:        file_name.c
* Description: Short description
* Note(s):     Definitions and information
*
*----------------------------------------------------------------------------*/

#include "robot_arm.h"
#include "button.h"
#include "motors.h"

void setup() {
  
  // Digital Inputs
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  pinMode(ENCODER_SW, INPUT); // active low
  pinMode(MODE, INPUT);
  
  // Setup button_t structs (boolean argument is active low flag)
  init_button(&mode, MODE, false);
  init_button(&encoder_sw, ENCODER_SW, true);
  
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
  
  // Debug
  Serial.begin(9600);
}

void loop() {
  update_button(&mode);
  update_button(&encoder_sw);
  
  if(check_button_hold(&mode)) {
    Serial.println("mode hold");
  }
  if(check_button_click(&mode)) {
    Serial.println("mode click");
  }
  if(check_button_hold(&encoder_sw)) {
    Serial.println("encoder hold");
  }
  if(check_button_click(&encoder_sw)) {
    Serial.println("encoder click");
  }
}
