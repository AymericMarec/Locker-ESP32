#include "SPI.h"
#include "MFRC522.h"
#include "MQTT/MQTT.hpp"
#include "Servo/Servo.hpp"
#include <WiFi.h>

#define RST_PIN   22  
#define SS_PIN    21  
#define MISO_PIN  19 
#define MOSI_PIN  23 
#define SCK_PIN   18 

MFRC522 mfrc522(SS_PIN, RST_PIN);

void RFID_Connect(){
    Serial.println("SPI initialisation");
    SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
    mfrc522.PCD_Init();
    delay(1000);
    mfrc522.PCD_DumpVersionToSerial();
}

boolean PICC_IsNewCardPresent(){
    return mfrc522.PICC_IsNewCardPresent();
}

void PICC_HaltA(){
    mfrc522.PICC_HaltA();
}

void PCD_StopCrypto1(){
    mfrc522.PCD_StopCrypto1();
}

boolean PICC_ReadCardSerial(){
    return mfrc522.PICC_ReadCardSerial();
}
void PrintUID(){
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
String GetUID(){
    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uidString += String(mfrc522.uid.uidByte[i], HEX);
        if (i < mfrc522.uid.size - 1) uidString += ":";
    }
    return uidString;
}
void Scan(){
    if(!IsOpen()){
        SendMessage(WiFi.macAddress()+"|"+GetUID(),"scan");
        Serial.print("UID Scan : ");
        Serial.println(GetUID());
        return;
    }
    SendMessage(WiFi.macAddress()+"|"+"close","door");
    CloseLocker();
}