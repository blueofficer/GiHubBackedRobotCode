#include "Arduino.h"
#include "ArmController.h"
#include "autoDrive.h"
#include "esp32-hal.h"
#include "motarContoller.h"
#include "music.h"
#include "myWifi.h"
#include "sonic.h"

// inbuilt led pin
#define LED_BUILTIN 2

// The line reading module
#define Left_Line 35
#define Center_Line 36
#define Right_Line 39

// Auto drive code
bool autoDrive = false;

// the current time in milisecnds
long timeRobotOn = 0;

boolean playingMusic = false;

void setup() {
  Serial.begin(115200);
  setupArmController();
  setUpWifi();
  setUpServerConnection();
  setUpMotar();
  setUpMusic();
  setUpSonicSensor();
  sendMessage("Hello from ESP32 over TCP!");
  pinMode(LED_BUILTIN, OUTPUT); // built in light
}

void doCommand(char *commandBuff) {
  if (commandBuff[0] == 'D') {
    autoDrive = false; // auto drive should turn off if it gets
    Move(commandBuff);
  } else if (commandBuff[0] == 'S') {
    unsigned int handAngle = ((unsigned int)commandBuff[1]);
    unsigned int wristAngle = ((unsigned int)commandBuff[2]);
    unsigned int elbowAngle = ((unsigned int)commandBuff[3]);
    unsigned int shoulderUpAngle = ((unsigned int)commandBuff[4]);
    unsigned int shoulderSideAngle = ((unsigned int)commandBuff[5]);

    setArmAngles(handAngle, wristAngle, elbowAngle, shoulderUpAngle,
                 shoulderSideAngle);

  } else if (commandBuff[0] == 'M') {
    playingMusic = !playingMusic;
    if (!playingMusic) {
      shutOfBuzzer();
    }
  } else if (commandBuff[0] == '3') {
    autoDrive = !autoDrive;
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

  if (playingMusic) {
    playNextNote(timeRobotOn);
  }

  // if (autoDrive) {
  //   selectStep(timeRobotOn);
  // }
  // Disabling this untill auto drive is lokey fixed
}