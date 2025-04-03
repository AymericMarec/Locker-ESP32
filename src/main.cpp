#include <Arduino.h>

#include "MQTT/MQTT.hpp"
#include "RFID/RFID.hpp"

#define RED_LED 26
#define GREEN_LED 27

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);

  ConnectWifi();
  ConnectMQTT();
  RFID_Connect();
  Subscribe("response");
}

void loop(){
  ListenMessage();
  static unsigned long lastScanTime = 0;
  const unsigned long scanCooldown = 3000; 

  if (millis() - lastScanTime < scanCooldown) {
    return; 
  }

  if (!PICC_IsNewCardPresent() || !PICC_ReadCardSerial()) {
    return;
  }
  SendMessage(GetUID(),"scan");
  Serial.println(GetUID());

  lastScanTime = millis(); 
  PICC_HaltA();    
  PCD_StopCrypto1();
}