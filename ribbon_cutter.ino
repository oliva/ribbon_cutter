#include <Servo.h>

// pins
#define pot A0
#define button A1
#define servo A2
#define heat A3
#define led LED_BUILTIN
Servo arm;

// params
#define angle_down 170
#define angle_up 30
#define speed_max 2
#define rest_top 250
#define rest_bottom 1000

// calculated
#if angle_down < angle_up
#define angle_dir 1
const int servo_steps = angle_up - angle_down;
#else
const int servo_steps = angle_down - angle_up;
#define angle_dir -1
#endif
int pos = angle_down;
unsigned long step_time = 2048 / servo_steps;

void setup() {
  pinMode(button, INPUT);
  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);
  pinMode(heat, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(heat, LOW);
  arm.attach(servo);
  arm.write(angle_down);
  delay(rest_bottom);
  arm.detach();
}

void loop() {
  // Wait for button release
  while (true) {
    if (digitalRead(button) == HIGH)
      break;
    else
      delay(1);
  }

  // Wait for button press
  while (true) {
    if (digitalRead(button) == LOW)
      break;
    else
      delay(1);
  }

  // Cycle start
  digitalWrite(led, HIGH);

  // Read pot to set speed
  step_time = ((unsigned long) analogRead(pot) * (unsigned long)speed_max) / (unsigned long)servo_steps;

  // Turn on heat, start servo
  digitalWrite(heat, HIGH);
  arm.attach(servo);

  // Raise arm
  for (pos = angle_down; pos != angle_up; pos += angle_dir) {
    arm.write(pos);
    delay(step_time);
  }

  // Turn off heat, wait a little
  digitalWrite(heat, LOW);
  delay(rest_top);

  // Lower arm, wait  a little, let servo rest
  arm.write(angle_down);
  delay(rest_bottom);
  arm.detach();
  digitalWrite(led, LOW);
}
