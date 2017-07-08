#include <PS2X_lib.h> 

#define PS2_DAT        13
#define PS2_CMD        11
#define PS2_SEL        10
#define PS2_CLK        12
#define pressures   false
#define rumble      false

#define LEFT_FORWARD_PIN 3
#define LEFT_REVERSE_PIN 5
#define RIGHT_FORWARD_PIN 6
#define RIGHT_REVERSE_PIN 9

PS2X ps2x;
int controllerType;

void setup() {
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT);
  
  delay(500);
  
  if(ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble) != 0) {
    // Error condition. Let's blink endlessly
    infiniteBlinking();
  }
  
  controllerType = ps2x.readType();
}

void loop() {
  
}

void infiniteBlinking() {
  int led = 13;
  while(true) {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
}
