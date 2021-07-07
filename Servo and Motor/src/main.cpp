#include <Arduino.h>

#define SERVO_CLAW PB_7
#define SERVO_ARM PB_9
#define SERVO_SWIVEL PB_8
#define SWITCH PB6

#define LEFT_MOTOR_A PA_0
#define LEFT_MOTOR_B PA_1
#define RIGHT_MOTOR_A PA_2
#define RIGHT_MOTOR_B PA_3

// MIN 500, MAX 2500
#define CLAW_CLOSE 700
#define CLAW_OPEN 1050
#define ARM_DOWN 500
#define ARM_UP 1500
#define SWIVEL_ORIGIN 2500
const int RESERVOIR_POSITIONS[3] = {1000, 1300, 1600};

#define MOTOR_FREQ 50
#define DC_FREQ 1000

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible

//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile int reservoir_state = 0; // how many cans are in the reservoir

//int angle_to_dutyCycle(int);
void store_can();

void setup()
{
  pinMode(SERVO_SWIVEL, OUTPUT);
  pinMode(SERVO_ARM, OUTPUT);
  pinMode(SERVO_CLAW, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(LEFT_MOTOR_A, OUTPUT);
  pinMode(LEFT_MOTOR_B, OUTPUT);
  pinMode(RIGHT_MOTOR_A, OUTPUT);
  pinMode(RIGHT_MOTOR_B, OUTPUT);

  pwm_start(SERVO_SWIVEL, MOTOR_FREQ, SWIVEL_ORIGIN, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
  delay(1000);
  pwm_start(SERVO_CLAW, MOTOR_FREQ, CLAW_CLOSE, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
  delay(1000);
  pwm_start(SERVO_ARM, MOTOR_FREQ, ARM_DOWN, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
  delay(1000);
  pwm_start(SERVO_CLAW, MOTOR_FREQ, CLAW_OPEN, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
  delay(1000);
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  /*display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello world!");
  display.display();
  delay(500);*/
}

void loop()
{
  pwm_start(LEFT_MOTOR_A, DC_FREQ, 2000, RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(LEFT_MOTOR_B, DC_FREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(RIGHT_MOTOR_A, DC_FREQ, 2000, RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(RIGHT_MOTOR_B, DC_FREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);

  delay(5000);

  pwm_start(LEFT_MOTOR_A, DC_FREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(LEFT_MOTOR_B, DC_FREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(RIGHT_MOTOR_A, DC_FREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(RIGHT_MOTOR_B, DC_FREQ, 0, RESOLUTION_12B_COMPARE_FORMAT);

  delay(2000);

  pwm_start(SERVO_CLAW, MOTOR_FREQ, CLAW_CLOSE, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);

  // while(true){
  //   if(digitalRead(SWITCH) == LOW){
  //     break;
  //   }
  // }
  store_can();
}

/*int angle_to_dutyCycle(int angle){
  return (angle * 11 + 500);
}*/

void store_can()
{
  //pwm_start(SERVO_CLAW, MOTOR_FREQ, CLAW_CLOSE, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);

  delay(2000);

  for (int i = ARM_DOWN; i < ARM_UP; i += 25)
  {
    pwm_start(SERVO_ARM, MOTOR_FREQ, i, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
    delay(15);
  }

  delay(2000);

  for (int i = SWIVEL_ORIGIN; i > RESERVOIR_POSITIONS[reservoir_state]; i -= 50)
  {
    pwm_start(SERVO_SWIVEL, MOTOR_FREQ, i, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
    delay(30);
  }

  delay(2000);

  pwm_start(SERVO_CLAW, MOTOR_FREQ, CLAW_OPEN, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);

  delay(2000);

  for (int i = RESERVOIR_POSITIONS[reservoir_state]; i < SWIVEL_ORIGIN; i += 50)
  {
    pwm_start(SERVO_SWIVEL, MOTOR_FREQ, i, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
    delay(30);
  }

  delay(2000);

  pwm_start(SERVO_CLAW, MOTOR_FREQ, CLAW_CLOSE, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);

  delay(1000);

  for (int i = ARM_UP; i > ARM_DOWN; i -= 25)
  {
    pwm_start(SERVO_ARM, MOTOR_FREQ, i, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
    delay(30);
  }

  delay(1000);

  pwm_start(SERVO_CLAW, MOTOR_FREQ, CLAW_OPEN, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);

  delay(2000);

  if (reservoir_state < 2)
  {
    reservoir_state++;
  }
  else
  {
    reservoir_state = 0;
  }
}
