#ifndef ArmController_H
#define ArmController_H

void setupArmController();
void setServoAngle(int servo, int angle);
void setArmAngles(bool handOpen,int wristAngle,int elbowAngle, int shoulderUpAngle, int shoulderSideAngle);
void resetPostions();

#endif