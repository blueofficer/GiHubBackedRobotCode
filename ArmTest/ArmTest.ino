#include "Arduino.h"
#include "ArmController.h"

void setup() {
  Serial.begin(115200);
  setupArmController();
  resetPostions();
}

void loop() {
  setArmAngles(false, 90, 90, 90, 90);
  delay(1000);
  setArmAngles(false, 90, 90, 90, 180);
  delay(1000);
  setArmAngles(false, 90, 90, 90, 90);
  delay(1000);
  setArmAngles(false, 90, 90, 90, 0);
  delay(1000);
}
