// Wifi stuff
#include <WiFi.h>
const char *ssid = "RobotWifi";
const char *password = "RobotWifi";
const char *deviceName = "JohnRobot";
IPAddress serverIP(192, 168, 50, 1);
constexpr uint16_t serverPort = 2222;

const int commandBuffSize = 10;
char commandBuff[commandBuffSize];

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

void sendMessage(char *message) { client.println(message); }

void sendMessage(const String &message) { client.println(message); }

void setUpServerConnection() {
  Serial.println("\nAttempting to connect to TCP server...");

  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server!");
  } else {
    Serial.println("Failed to connect to server.");
  }
}

void resetReadWriteBufferPlace() {
  currentPlaceRead = 0;
  currentPlaceWrite = 0;
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