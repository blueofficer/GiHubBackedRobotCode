#include "Arduino.h"
#include <ESP32Servo.h>

#define SERVO_HAND_PIN 4
#define SERVO_WRIST_PIN 25
#define SERVO_ELBOW_PIN 26
#define SERVO_SHOULDER_UP_PIN 27
#define SERVO_SHOULDER_SIDE_PIN 34

Servo ServoHand;
Servo ServoWrist;
Servo ServoElbow;
Servo ServoShoulderUp;
Servo ServoShoulderSide;

void resetPostions() {
  ServoWrist.write(90);
  ServoElbow.write(60);
  ServoShoulderUp.write(0);
  ServoShoulderSide.write(0);
}

void setArmAngles(int handAngle, int wristAngle, int elbowAngle,
                  int shoulderUpAngle, int shoulderSideAngle) {

  ServoHand.write(constrain(handAngle, 0, 180));
  ServoWrist.write(constrain(wristAngle, 0, 180));
  ServoElbow.write(constrain(elbowAngle, 0, 180));
  ServoShoulderUp.write(constrain(shoulderUpAngle, 0, 180));
  ServoShoulderSide.write(constrain(shoulderSideAngle, 0, 180));
}

void setServoAngle(int servo, int angle) {
  if (servo == 0) {
    ServoWrist.write(angle);
  } else if (servo == 1) {
    ServoElbow.write(angle);
  } else if (servo == 2) {
    ServoShoulderUp.write(angle);
  } else if (servo == 3) {
    ServoShoulderSide.write(angle);
  }
}

void setupArmController() {
  ServoHand.attach(SERVO_HAND_PIN);
  ServoWrist.attach(SERVO_WRIST_PIN);
  ServoElbow.attach(SERVO_ELBOW_PIN);
  ServoShoulderUp.attach(SERVO_SHOULDER_UP_PIN);
  ServoShoulderSide.attach(SERVO_SHOULDER_SIDE_PIN);
}
