#include <ESP32Servo.h>
#include "Arduino.h"

// servo pi
#define SERVO_PIN 25

int changeInAngle = 10;
int servoAngle = 90;
unsigned long timeWhenShouldRotate = 0;
int movmentintervol = 500; // ts in millisenceds 500 is half a secend

Servo myServo;

void setUpServo() {
  myServo.attach(25);
  Serial.println("Servo and ultrasonic sensor ready!");
}

void setServoAngle(int angle) {
  angle = constrain(angle, 0, 180);
  servoAngle = angle;
  myServo.write(angle);
}

void autoRotateServo(int timeRobotOn) {
  if (timeWhenShouldRotate <= timeRobotOn) {
    timeWhenShouldRotate = millis() + movmentintervol;

    if (servoAngle >= 170) {
      changeInAngle = -10;
    } else if (servoAngle <= 10) {
      changeInAngle = 10;
    }

    servoAngle += changeInAngle;

    setServoAngle(servoAngle);
  }
}