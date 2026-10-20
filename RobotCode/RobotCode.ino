#include "Arduino.h"
#include "esp32-hal.h"

// THe ultrasonic sensore
#define TRIG_PIN 13
#define ECHO_PIN 14

// servo pi
#define SERVO_PIN 25

// inbuilt led pin
#define LED_BUILTIN 2

// Notes
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

int melody[] = {

    // Never Gonna Give You Up - Rick Astley
    // Score available at
    // https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
    // Arranged by Chlorondria

    NOTE_D5,  -4, NOTE_E5,  -4, NOTE_A4,  4, // 1
    NOTE_E5,  -4, NOTE_FS5, -4, NOTE_A5,  16, NOTE_G5,  16, NOTE_FS5, 8,
    NOTE_D5,  -4, NOTE_E5,  -4, NOTE_A4,  2,  NOTE_A4,  16, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  8,  NOTE_D5,  16, NOTE_D5,  -4, NOTE_E5,  -4,
    NOTE_A4,  4, // repeat from 1
    NOTE_E5,  -4, NOTE_FS5, -4, NOTE_A5,  16, NOTE_G5,  16, NOTE_FS5, 8,
    NOTE_D5,  -4, NOTE_E5,  -4, NOTE_A4,  2,  NOTE_A4,  16, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  8,  NOTE_D5,  16, REST,     4,  NOTE_B4,  8,
    NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_D5,  8,  NOTE_E5,  8,  NOTE_CS5, -8,
    NOTE_B4,  16, NOTE_A4,  2,  REST,     4,

    REST,     8,  NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  4,  NOTE_A4,  8, // 7
    NOTE_A5,  8,  REST,     8,  NOTE_A5,  8,  NOTE_E5,  -4, REST,     4,
    NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_B4,  8,
    NOTE_D5,  8,  NOTE_E5,  8,  REST,     8,  REST,     8,  NOTE_CS5, 8,
    NOTE_B4,  8,  NOTE_A4,  -4, REST,     4,  REST,     8,  NOTE_B4,  8,
    NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_B4,  8,  NOTE_A4,  4,
    NOTE_E5,  8,  NOTE_E5,  8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  4,
    REST,     4,

    NOTE_D5,  2,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_D5,  8, // 13
    NOTE_E5,  8,  NOTE_E5,  8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  4,
    NOTE_A4,  4,  REST,     2,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8,  REST,     8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  -4,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_FS5, -8,
    NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16,

    NOTE_E5,  -8, NOTE_E5,  -8, NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  -8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, // 18
    NOTE_D5,  4,  NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  8,
    NOTE_A4,  8,  NOTE_A4,  8,  NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_FS5, -8, NOTE_FS5, -8,
    NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,
    NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,

    NOTE_D5,  4,  NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,
    NOTE_A4,  8, // 23
    NOTE_E5,  4,  NOTE_D5,  2,  REST,     4,  REST,     8,  NOTE_B4,  8,
    NOTE_D5,  8,  NOTE_B4,  8,  NOTE_D5,  8,  NOTE_E5,  4,  REST,     8,
    REST,     8,  NOTE_CS5, 8,  NOTE_B4,  8,  NOTE_A4,  -4, REST,     4,
    REST,     8,  NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8,  NOTE_A4,  4,  REST,     8,  NOTE_A5,  8,  NOTE_A5,  8,
    NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  8,  NOTE_D5,  8,

    REST,     8,  NOTE_A4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8, // 29
    REST,     8,  NOTE_CS5, 8,  NOTE_B4,  8,  NOTE_A4,  -4, REST,     4,
    NOTE_B4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,  NOTE_B4,  8,
    NOTE_A4,  4,  REST,     8,  REST,     8,  NOTE_E5,  8,  NOTE_E5,  8,
    NOTE_FS5, 4,  NOTE_E5,  -4, NOTE_D5,  2,  NOTE_D5,  8,  NOTE_E5,  8,
    NOTE_FS5, 8,  NOTE_E5,  4,  NOTE_E5,  8,  NOTE_E5,  8,  NOTE_FS5, 8,
    NOTE_E5,  8,  NOTE_A4,  8,  NOTE_A4,  4,

    REST,     -4, NOTE_A4,  8,  NOTE_B4,  8,  NOTE_CS5, 8,  NOTE_D5,  8,
    NOTE_B4,  8, // 35
    REST,     8,  NOTE_E5,  8,  NOTE_FS5, 8,  NOTE_E5,  -4, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_FS5, -8, NOTE_FS5, -8,
    NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,
    NOTE_E5,  -8, NOTE_E5,  -8, NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_D5,  4,
    NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,  NOTE_A4,  8,

    NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16, // 40
    NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16,
    NOTE_D5,  16, NOTE_B4,  16, NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8,
    NOTE_CS5, 16, NOTE_B4,  8,  NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16, NOTE_D5,  4,  NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16,
    NOTE_A4,  4,  NOTE_A4,  8,  NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16,

    NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16, NOTE_B4,  16,
    NOTE_D5,  16, NOTE_B4,  16, // 45
    NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_D5,  4,
    NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,  NOTE_A4,  8,
    NOTE_E5,  4,  NOTE_D5,  2,  NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16,
    NOTE_B4,  16, NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5,  -4, NOTE_A4,  16,
    NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, // 45

    NOTE_A5,  4,  NOTE_CS5, 8,  NOTE_D5,  -8, NOTE_CS5, 16, NOTE_B4,  8,
    NOTE_A4,  16, NOTE_B4,  16, NOTE_D5,  16, NOTE_B4,  16, NOTE_D5,  4,
    NOTE_E5,  8,  NOTE_CS5, -8, NOTE_B4,  16, NOTE_A4,  4,  NOTE_A4,  8,

    NOTE_E5,  4,  NOTE_D5,  2,  REST,     4};

// Music
int bpm = 120; // Beats per minute
int currentSong = 0;
int currentNote = 0;
int maxNote = 678;
long timeOfNextNote = 0;
boolean playingMusic = false;

// Buzzer pi
#define Buzzer 33

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

#include <ESP32Servo.h>

// Wifi stuff
#include <WiFi.h>
const char *ssid = "RobotWifi";
const char *password = "RobotWifi";
const char *deviceName = "JohnRobot";
IPAddress serverIP(192, 168, 8, 223);
constexpr uint16_t serverPort = 4444;

// Command Buffer
const int commandBuffSize = 10;
char commandBuff[commandBuffSize];

// Reading and writing to the command buffer
int currentPlaceRead = 0;
int currentPlaceWrite = 0;

// Auto rotate the servo
bool rotateServo = false;
int changeInAngle = 10;
int servoAngle = 90;
unsigned long timeWhenShouldRotate = 0;
int movmentintervol = 500; // ts in millisenceds 500 is half a secend

// the current time in milisecnds
long timeRobotOn = 0;

Servo myServo;
WiFiClient client;

void setUpWifi() {
  WiFi.setHostname(deviceName);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("Device name: ");
  Serial.println(WiFi.getHostname());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setUpServerConnection(IPAddress serverIP, uint16_t serverPort) {
  Serial.println("\nAttempting to connect to TCP server...");

  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server!");
  } else {
    Serial.println("Failed to connect to server.");
  }
}

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

void playNextNote() {
  Serial.println("playing note");

  if (currentNote >= maxNote) {
    currentNote = 0;
  }

  int divider = melody[currentNote + 1];
  int noteDuration = 0;
  int wholenote = (60000 * 4) / bpm;

  if (divider > 0) {
    // regular note, just proceed
    noteDuration = (wholenote) / divider;
  } else if (divider < 0) {
    // dotted notes are represented with negative durations!!
    noteDuration = (wholenote) / abs(divider);
    noteDuration *= 1.5; // increases the duration in half for dotted notes
  }

  if (timeRobotOn >= timeOfNextNote) {
    noTone(Buzzer);
    timeOfNextNote = noteDuration + timeRobotOn;
    tone(Buzzer, melody[currentNote]);
    currentNote += 2; // current note
  }
}

void setup() {
  Serial.begin(115200);
  setUpServo();
  setUpWifi();
  setUpServerConnection(serverIP, serverPort);
  setUpMotar();

  sendMessage("Hello from ESP32 over TCP!");

  pinMode(LED_BUILTIN, OUTPUT); // built in light
  pinMode(Buzzer, OUTPUT);

  turnServo(90);
}

void sendMessage(char *message) { client.println(message); }

void sendMessage(const String &message) { client.println(message); }

void resetReadWriteBufferPlace() {
  currentPlaceRead = 0;
  currentPlaceWrite = 0;
}

void doCommand() {
  if (commandBuff[0] == 'D') {
    Move();
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
      noTone(Buzzer);
    }
  } else {
    Serial.print("Unknow command: " + commandBuff[0]);
  }
}

int readNextByte() {
  if (!client.connected()) {
    return -1; // Connection lost
  }

  if (!client.available()) {
    return 0; // No data yet
  }

  if (currentPlaceWrite >= commandBuffSize) {
    resetReadWriteBufferPlace();
    return -1; // Buffer overflow
  }

  char tempByte = client.read();
  commandBuff[currentPlaceWrite++] = tempByte;

  if (tempByte == '\n') {
    return 1; // Complete command
  }

  return 0; // Keep reading
}

void Move() {
  if (currentPlaceWrite != 6) { // makes sure the comamnd is the right size it
                                // should look like (DFFFF'\n')
    return;
  }

  Serial.print(commandBuff[1]); // prints the dir for error checking
  Serial.print(commandBuff[2]);
  Serial.print(commandBuff[3]);
  Serial.print(commandBuff[4]);
  Serial.print('\n');

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
    doCommand();
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
    playNextNote();
  }
}