#include "MFRC522.h"

#ifndef RFID_HPP
#define RFID_HPP

void RFID_Connect();
boolean PICC_IsNewCardPresent();
boolean PICC_ReadCardSerial();
void PrintUID();
String GetUID();
#endif