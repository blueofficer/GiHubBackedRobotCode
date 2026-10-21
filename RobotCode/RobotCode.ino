#include "Arduino.h"
#include "esp32-hal.h"
#include "music.h"
#include <ESP32Servo.h>
#include "myWifi.h"
#include "motarContoller.h"

// THe ultrasonic sensore
#define TRIG_PIN 13
#define ECHO_PIN 14

// servo pi
#define SERVO_PIN 25

// inbuilt led pin
#define LED_BUILTIN 2

// The line reading module
#define Left_Line 35
#define Center_Line 36
#define Right_Line 39

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