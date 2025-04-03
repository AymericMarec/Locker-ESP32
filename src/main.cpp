#include <Arduino.h>

#include "MQTT/MQTT.hpp"
#include "RFID/RFID.hpp"

#define LED_PIN 26

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  ConnectWifi();
  ConnectMQTT();
  RFID_Connect();
  Subscribe("response");
}

void loop(){
  static unsigned long lastScanTime = 0;
  const unsigned long scanCooldown = 3000; 

  if (millis() - lastScanTime < scanCooldown) {
    return; 
  }

  if (!PICC_IsNewCardPresent() || !PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(GetUID());

  lastScanTime = millis(); 
  PICC_HaltA();    
  PCD_StopCrypto1();
}