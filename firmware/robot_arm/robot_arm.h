/*----------------------------------------------------------------------------
 * Name:        file_name.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include "button.h"
#include "motors.h"
#include "encoder.h"
#include "led.h"
#include "position_list.h"

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
#define NUM_ARM_STATES 3
#define NUM_LEDS 6 // 1 virtual LED
#define NUM_AXIS_LEDS 5
#define DEFAULT_STEPPER_SPEED 140 // degrees/second
#define MAX_BASE_ROTATION 720

// Startup servo positions
#define GRIPPER_STARTUP_POS 100
#define WRIST_STARTUP_POS 5
#define ELBOW_STARTUP_POS 180
#define SHOULDER_STARTUP_POS 50
#define GRIPPER_UPPER_LIMIT 100

// State Machine
enum top_level_state_machine {
  REMOTE,
  KNOB,
  PLAY
};

top_level_state_machine robot_arm_state = REMOTE;

// LED Objects
led_t stat_led = led_t(STAT, true);
led_t gripper_led = led_t(GRIPPER_LED, true);
led_t forearm_led = led_t(FOREARM_LED, true);
led_t upper_arm_led = led_t(UPPER_LED, true);
led_t base_led = led_t(BASE_LED, false);

// Non axis LEDs must be stored at the end of the led_list
// There are two gripper LEDs on pupose because the gripper_led is solid when
//  the wrist is moving and flashing for the gripper. A double entry in the list
//  allows 1 to 1 correspondence between the led_list and the counter_list;
led_t* led_list[NUM_LEDS] = {&gripper_led, &gripper_led, &forearm_led,
                             &upper_arm_led, &base_led, &stat_led};

// Buttons Objects
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

servo_motor_t* servo_list[5] = {&gripper, &wrist, &elbow, &shoulder1, &shoulder2};

// Write to motors flag
bool write_to_motors = false; 

// Record toolpath
position_list_t toolpath = position_list_t();
int target_coordiante = 0;
long max_servo_eta = 0;
bool cycle_start = false; 

#endif __ROBOT_ARM__






