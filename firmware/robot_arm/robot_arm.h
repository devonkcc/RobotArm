/*----------------------------------------------------------------------------
 * Name:        file_name.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include "button.h"
#include "motors.h"

#ifndef __ROBOT_ARM__
#define __ROBOT_ARM__

// Controller Pinout

#define ENCODER_A 2
#define DIR 3
#define STEP 4
#define SHOULDER_PWM1 5
#define SHOULDER_PWM2 6
#define UPPER_LED 7
#define FOREARM_LED 8
#define ELBOW_PWM 9
#define WRIST_PWM 10
#define GRIP_PWM 11
#define GRIP_LED 12
#define STAT 13
#define D_AUX A0
#define HALL_SIGNAL A1
#define ENABLE A2
#define MODE A3
#define ENCODER_SW A4 // active low
#define ENCODER_B A5
#define HP_SENSE A6
#define A_AUX A7

// State Machine

enum RobotArmState {
  REMOTE,
  MANUAL,
  RECORD,
  PLAY,
  NUM_ARM_STATES
};

RobotArmState st_robot_arm_state = REMOTE;

// Buttons

button_t mode;
button_t encoder_sw;

#endif __ROBOT_ARM__


