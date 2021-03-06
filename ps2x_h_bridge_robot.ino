#include <PS2X_lib.h>

#define PS2_DAT        14
#define PS2_CMD        15
#define PS2_SEL        16
#define PS2_CLK        17
#define pressures   false
#define rumble      false

//#define D_PAD_DRIVE
//#define RIGHT_STICK_DRIVE

#ifdef RIGHT_STICK_DRIVE
  #define DRIVE_STICK_X PSS_RX
  #define DRIVE_STICK_Y PSS_RY
#else
  #define DRIVE_STICK_X PSS_LX
  #define DRIVE_STICK_Y PSS_LY
#endif

#define LEFT_FORWARD_PIN 3
#define LEFT_REVERSE_PIN 5
#define RIGHT_FORWARD_PIN 6
#define RIGHT_REVERSE_PIN 7

PS2X ps2x;

int xValue;
int yValue;
int throttleInput;
int steeringInput;
int leftMotorOutput;
int rightMotorOutput;

void setup() {
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT);
  
  boolean controllerConfigured = false;
  boolean correctControllerType = false;
  
  while(!controllerConfigured && !correctControllerType) {
    controllerConfigured = (ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble) == 0);
    correctControllerType = (ps2x.readType() == 1);
    delay(500);
  }

}

void loop() {
  delay(10);
  
  if(ps2x.read_gamepad(false, 0)) {

#ifndef D_PAD_DRIVE

    xValue = ps2x.Analog(DRIVE_STICK_X);
    yValue = ps2x.Analog(DRIVE_STICK_Y);

#else

    if(ps2x.Button(PSB_PAD_UP)) {
      yValue = 0;
    }
    else if(ps2x.Button(PSB_PAD_DOWN)) {
      yValue = 255;
    }
    else {
      yValue = 128;
    }

    if(ps2x.Button(PSB_PAD_LEFT)) {
      xValue = 0;
    }
    else if(ps2x.Button(PSB_PAD_RIGHT)) {
      xValue = 255;
    }
    else {
      xValue = 128;
    }

#endif

  }
  else {
    xValue = 128;
    yValue = 128;
  }
  
  // Upper left on stick is (0,0), lower right is (255, 255)
  throttleInput = constrain((yValue - 128) * -2, -255, 255);
  steeringInput = constrain((xValue - 128) * 2, -255, 255);
  
  leftMotorOutput = constrain(throttleInput + steeringInput, -255, 255);
  rightMotorOutput = constrain(throttleInput - steeringInput, -255, 255);
  
  if(leftMotorOutput > 0) {
    analogWrite(LEFT_FORWARD_PIN, leftMotorOutput);
    digitalWrite(LEFT_REVERSE_PIN, LOW);
  }
  else {
    digitalWrite(LEFT_FORWARD_PIN, LOW);
    analogWrite(LEFT_REVERSE_PIN, abs(leftMotorOutput));
  }
  
  if(rightMotorOutput > 0) {
    analogWrite(RIGHT_FORWARD_PIN, rightMotorOutput);
    digitalWrite(RIGHT_REVERSE_PIN, LOW);
  }
  else {
    digitalWrite(RIGHT_FORWARD_PIN, LOW);
    analogWrite(RIGHT_REVERSE_PIN, abs(rightMotorOutput));
  }
  
}

void infiniteBlinking(int blinkDelay) {
  int led = 13;
  while(true) {
    digitalWrite(led, HIGH);
    delay(blinkDelay);
    digitalWrite(led, LOW);
    delay(blinkDelay);
  }
}
