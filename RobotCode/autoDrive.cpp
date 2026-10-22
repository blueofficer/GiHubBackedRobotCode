#include "Arduino.h"
#include "motarContoller.h"
#include "servoController.h"
#include "sonic.h"

float headRoom = 10.0; // Head room the

int currentStep = 0;

float leftDistince = 0;

float rightDistince = 0;

float timeToStopMoving =
    2; // how long the robot should turn for to go 90 degress

void resetCurrentStep() { currentStep = 0; }

void step0() {
  stopMotars();
  currentStep++;
}

void step1() {
  if (readDistance() > headRoom) {
    void setMotarsForword();
  } else {
    currentStep++;
  }
}

void step2() {
  setServoAngle(0);
  leftDistince = readDistance();
  currentStep++;
}

void step3() {
  setServoAngle(180);
  rightDistince = readDistance();
  currentStep++;
}

void step4(long currentTime) {
  if (rightDistince > leftDistince) {
    turnRight();
  } else {
    turnLeft();
  }

  timeToStopMoving = currentTime + timeToStopMoving;
}

void step5(long currentTime) {
  if (currentTime >= timeToStopMoving) {
    stopMotars();
    resetCurrentStep();
  }
}

void selectStep(long currentTime) {
  switch (currentStep) {
  case 0:
    step0();
    break;
  case 1:
    step1();
    break;
  case 2:
    step2();
    break;
  case 3:
    step3();
    break;
  case 4:
    step4(currentTime);
    break;
  case 5:
    step5(currentTime);
    break;

  default:
    stopMotars();
    resetCurrentStep();
    break;
  }
}