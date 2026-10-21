#include "Arduino.h"
#include "esp32-hal.h"
#include "music.h"
#include <ESP32Servo.h>
#include "myWifi.h"

// THe ultrasonic sensore
#define TRIG_PIN 13
#define ECHO_PIN 14

// servo pi
#define SERVO_PIN 25

// inbuilt led pin
#define LED_BUILTIN 2

// Motart controller pin
#define PWM1_PIN 19 // right
#define PWM2_PIN 23 // left
#define SHCP_PIN 18
#define EN_PIN 16
#define DATA_PIN 5
#define STCP_PIN 17

// The line reading module
#define Left_Line 35
#define Center_Line 36
#define Right_Line 39

// Motart contoller numbers there powers of 2
#define M1_Forward 128
#define M1_Backward 64
#define M2_Forward 32
#define M2_Backward 16
#define M3_Forward 2
#define M3_Backward 4
#define M4_Forward 1
#define M4_Backward 8

// Auto rotate the servo
bool rotateServo = false;
int changeInAngle = 10;
int servoAngle = 90;
unsigned long timeWhenShouldRotate = 0;
int movmentintervol = 500; // ts in millisenceds 500 is half a secend

// the current time in milisecnds
long timeRobotOn = 0;

boolean playingMusic = false;

Servo myServo;

void setUpServo() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  myServo.attach(25);
  Serial.println("Servo and ultrasonic sensor ready!");
}

void setUpMotar() {
  pinMode(SHCP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(STCP_PIN, OUTPUT);
  pinMode(PWM1_PIN, OUTPUT);
  pinMode(PWM2_PIN, OUTPUT);
}

void setup() {
  Serial.begin(115200);
  setUpServo();
  setUpWifi();
  setUpServerConnection();
  setUpMotar();
  setUpMusic();

  sendMessage("Hello from ESP32 over TCP!");

  pinMode(LED_BUILTIN, OUTPUT); // built in light

  turnServo(90);
}

void doCommand(char* commandBuff) {


  if (commandBuff[0] == 'D') {
    Move(commandBuff);
  } else if (commandBuff[0] == 'S' && !rotateServo) {
    turnServo((int)commandBuff[1]);
    Serial.print("New Angle");
    Serial.print((int)commandBuff[1]);
    Serial.print(":");
    Serial.print(commandBuff[1]);
    Serial.print('\n');
  } else if (commandBuff[0] == '1') {
    rotateServo = !rotateServo;
  } else if (commandBuff[0] == 'M') {
    playingMusic = !playingMusic;
    if (!playingMusic) {
      shutOfBuzzer();
    }
  } else {
    Serial.print("Unknow command: " + commandBuff[0]);
  }
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

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1.0;
  }

  return duration * 0.0343 / 2.0;
}

void turnServo(int angle) {
  angle = constrain(angle, 0, 180);
  servoAngle = angle;
  myServo.write(angle);
}

void loop() {
  int replyCode = readNextByte();

  timeRobotOn = millis();

  if (replyCode == 1) {
    doCommand(getCommandBufferPointer());
    resetReadWriteBufferPlace();
  } else if (replyCode == -1) {
    resetReadWriteBufferPlace();
  }

  if (rotateServo && timeWhenShouldRotate <= timeRobotOn) {
    timeWhenShouldRotate = millis() + movmentintervol;

    if (servoAngle >= 170) {
      changeInAngle = -10;
    } else if (servoAngle <= 10) {
      changeInAngle = 10;
    }

    servoAngle += changeInAngle;

    turnServo(servoAngle);
  }

  if (playingMusic) {
    playNextNote(timeRobotOn);
  }
}