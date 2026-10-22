#include "Arduino.h"
#include "esp32-hal.h"
#include "music.h"
#include "myWifi.h"
#include "motarContoller.h"
#include "servoController.h"
#include "sonic.h"
#include "autoDrive.h"

// inbuilt led pin
#define LED_BUILTIN 2

// The line reading module
#define Left_Line 35
#define Center_Line 36
#define Right_Line 39

// Auto rotate the servo
bool rotateServo = false;

//Auto drive code
bool autoDrive = true;

// the current time in milisecnds
long timeRobotOn = 0;

boolean playingMusic = false;

void setup() {
  Serial.begin(115200);
  setUpServo();
  setUpWifi();
  setUpServerConnection();
  setUpMotar();
  setUpMusic();
  setUpSonicSensor();
  sendMessage("Hello from ESP32 over TCP!");
  pinMode(LED_BUILTIN, OUTPUT); // built in light
  setServoAngle(90);
}

void doCommand(char* commandBuff) {
  if (commandBuff[0] == 'D') {
    autoDrive = false; //auto drive should turn off if it gets 
    Move(commandBuff);
  } else if (commandBuff[0] == 'S' && !rotateServo) {
    setServoAngle((int)commandBuff[1]);
  } else if (commandBuff[0] == '1') {
    rotateServo = !rotateServo;
  } else if (commandBuff[0] == 'M') {
    playingMusic = !playingMusic;
    if (!playingMusic) {
      shutOfBuzzer();
    }
  }else if(commandBuff[0] == 'A'){
    //TODO: implment auto drive
  } else {
    Serial.print("Unknow command: " + commandBuff[0]);
  }
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

  if (rotateServo) {
    autoRotateServo(timeRobotOn);
  }

  if (playingMusic) {
    playNextNote(timeRobotOn);
  }

  if(autoDrive){
    selectStep(timeRobotOn);
  }
}