#include "Arduino.h"

// Motart controller pin
#define PWM1_PIN 19 // right
#define PWM2_PIN 23 // left
#define SHCP_PIN 18
#define EN_PIN 16
#define DATA_PIN 5
#define STCP_PIN 17

// Motart contoller numbers there powers of 2
#define M1_Forward 128
#define M1_Backward 64
#define M2_Forward 32
#define M2_Backward 16
#define M3_Forward 2
#define M3_Backward 4
#define M4_Forward 1
#define M4_Backward 8

void setUpMotar() {
  pinMode(SHCP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(STCP_PIN, OUTPUT);
  pinMode(PWM1_PIN, OUTPUT);
  pinMode(PWM2_PIN, OUTPUT);
}

void Move(char* commandBuff) {
  int MotarVals = 0; //

  if (commandBuff[1] == 'F') {
    MotarVals += M1_Forward;
  } else if (commandBuff[1] == 'B') {
    MotarVals += M1_Backward;
  }

  if (commandBuff[2] == 'F') {
    MotarVals += M2_Forward;
  } else if (commandBuff[2] == 'B') {
    MotarVals += M2_Backward;
  }

  if (commandBuff[3] == 'F') {
    MotarVals += M3_Forward;
  } else if (commandBuff[3] == 'B') {
    MotarVals += M3_Backward;
  }

  if (commandBuff[4] == 'F') {
    MotarVals += M4_Forward;
  } else if (commandBuff[4] == 'B') {
    MotarVals += M4_Backward;
  }

  digitalWrite(EN_PIN, LOW);
  analogWrite(PWM1_PIN, 255);
  analogWrite(PWM2_PIN, 255);

  digitalWrite(STCP_PIN, LOW);
  shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, MotarVals);
  digitalWrite(STCP_PIN, HIGH);
}