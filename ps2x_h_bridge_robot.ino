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

void setup() {
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT);
  
  delay(500);
  
  if(ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble) != 0) {
    // Error condition. Let's blink endlessly
    infiniteBlinking(1000);
  }
  
  if(ps2x.readType() != 1) {
    // Wrong controller type. Blink on, brother!
    infiniteBlinking(2000);
  }
}

void loop() {
  ps2x.read_gamepad(false, 0);
  
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
