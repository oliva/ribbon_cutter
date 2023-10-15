#include <Servo.h>

// pins
#define pot A0
#define button A1
#define servo A2
#define heat A3
#define led LED_BUILTIN
Servo arm;
uint8_t pos = 0;

// params
#define servo_start 170
#define servo_end 30
#define servo_step -1
#define speed_max 2
const uint8_t servo_steps = servo_end - servo_start;
unsigned long step_time = 2048 / servo_steps;

void setup() {
  arm.attach(servo);
  pinMode(button, INPUT);
  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);
  pinMode(heat, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(heat, LOW);
}

void loop() {
  // Wait for button press
  while (true) {
    if (digitalRead(button) == LOW)
      break;
    else
      delay(1);
  }

  //Read pot to set speed
  step_time = analogRead(pot) * speed_max / servo_steps;

  // Turn on heat
  digitalWrite(led, HIGH);
  digitalWrite(heat, HIGH);

  // Raise arm
  for (pos = servo_start; pos <= servo_end; pos += servo_step) {
    arm.write(pos);
    delay(step_time);

  }

  // Wait a little
  delay(200);

  // Lower arm
  for (pos = servo_end; pos >= servo_start; pos -= servo_step) {
    arm.write(pos);
    delay(step_time);
  }

  // Turn off heat
  digitalWrite(led, LOW);
  digitalWrite(heat, LOW);
}