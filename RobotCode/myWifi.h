#ifndef myWifi_H
#define myWifi_H

void setUpWifi();
void sendMessage();

void sendMessage(char *message);
void sendMessage(const String &message);
void setUpServerConnection();

void resetReadWriteBufferPlace();

int readNextByte();

char* getCommandBufferPointer();

#endif