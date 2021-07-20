#pragma once
// bluepill pin assignment
#define CLAW_SERVO PA_8
#define ARM_SERVO PA_9
#define SWIVEL_SERVO PA_10
#define RESERVOIR_SERVO PB_8

#define LEFT_TAPE_SENSOR PB0
#define RIGHT_TAPE_SENSOR PB1
#define FRONT_DROPOFF_SENSOR PB10
#define CLAW_SENSOR PA7
#define P_POT PA4
#define D_POT PA5
#define I_POT PA6

// A = forward, B = backward
#define LEFT_WHEEL_A PA_0
#define LEFT_WHEEL_B PA_1
#define RIGHT_WHEEL_A PA_2
#define RIGHT_WHEEL_B PA_3
#define FLAPPER_MOTOR PB_9

const double RW_ADJUSTMENT_FACTOR = 0.8;
const int MAX_INTEGRATOR_VALUE = 4000;

// Adafruit Display: PB6, PB7

const int SERVO_FREQ = 50;
const int DC_FREQ = 1000;
const int CRUISING_SPEED = 2150;
const int DROPOFF_SPEED = 1000;
const int FLAPPER_SPEED = 650; 

// Servo Position
// MIN 500, MAX 2500
// blake - 700, brian - 720, tara = 750
const int CLAW_CLOSE = 720;
const int CLAW_OPEN = 1050;
const int ARM_DOWN = 500;
const int ARM_UP = 1500;
const int SWIVEL_ORIGIN = 2500;
const int RESERVOIR_POSITIONS[3] = {1150, 1450, 1800};
const int RESERVOIR_OPEN = 1000;
const int RESERVOIR_CLOSE = 500;

const int CAN_SENSING_THRESHOLD = 200;
const int TIME_TO_GRAB_CAN_THRESHOLD = 500;
const int BW_THRES = 100; // Black > 100, White < 100 approx
// const int GREY1_2 = 2;
// const int GREY2_3 = 3;
// const int GREY3_BLACK = 5;

// display set-up
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible
