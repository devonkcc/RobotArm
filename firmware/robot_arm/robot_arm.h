/*----------------------------------------------------------------------------
 * Name:        file_name.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include "button.h"
#include "motors.h"
#include "encoder.h"

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
#define GRIPPER_PWM 11
#define GRIPPER_LED 12
#define STAT 13
#define BASE_LED A0
#define HALL_SIGNAL A1
#define ENABLE A2
#define MODE A3
#define ENCODER_SW A4 // active low
#define ENCODER_B A5
#define HP_SENSE A6
#define A_AUX A7

// Constants
#define NUM_MOTORS 5
#define DEFAULT_STEPPER_SPEED 140 // degrees/second

// State Machine
enum top_level_state_machine {
  REMOTE,
  MANUAL,
  RECORD,
  PLAY,
  PLAY_WAITING,
  NUM_ARM_STATES
};

top_level_state_machine robot_arm_state = REMOTE;

// Buttons
// Setup button_t structs (boolean argument is active low flag)
button_t mode = button_t(MODE, false);
button_t encoder_sw = button_t(ENCODER_SW, true);

// Encoder
encoder_t encoder = encoder_t(ENCODER_A, ENCODER_B);

// Global Axix Poisitions
counter_t gripper_angle;
counter_t wrist_angle;
counter_t elbow_angle;
counter_t shoulder_angle;
counter_t base_angle;

counter_t* counter_list [NUM_MOTORS] = {&gripper_angle, &wrist_angle,
                                        &elbow_angle, &shoulder_angle,
                                        &base_angle};
int curr_counter = 4;

// Servo objects
Servo gripper_servo;
Servo wrist_servo;
Servo elbow_servo;
Servo shoulder_servo1;
Servo shoulder_servo2;

// Motors objects
servo_motor_t gripper = servo_motor_t(GRIPPER_PWM, &gripper_servo, 1, 0,
                                      SMALL_SERVO_SPEED);
servo_motor_t wrist = servo_motor_t(WRIST_PWM, &wrist_servo, 1, 0,
                                    SMALL_SERVO_SPEED);
servo_motor_t elbow = servo_motor_t(ELBOW_PWM, &elbow_servo, 1, 0,
                                    LARGE_SERVO_SPEED);
servo_motor_t shoulder1 = servo_motor_t(SHOULDER_PWM1, &shoulder_servo1, 1, 0,
                                        LARGE_SERVO_SPEED);
servo_motor_t shoulder2 = servo_motor_t(SHOULDER_PWM2, &shoulder_servo2, -1, 180,
                                        LARGE_SERVO_SPEED);
stepper_motor_t base = stepper_motor_t(DIR, STEP, ENABLE);

// Stepper global variables
extern volatile bool timing_pin_state;
extern volatile int steps_remaining;
extern volatile bool stepper_dn;

#endif __ROBOT_ARM__






