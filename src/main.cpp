#include <Arduino.h>

#include "MQTT/MQTT.hpp"
#include "RFID/RFID.hpp"
#include "WiFi/WiFi.hpp"
#include "Servo/Servo.hpp"
#include <ESP32Servo.h>
#include <WiFi.h>

#define RED_LED 26
#define GREEN_LED 27

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);


  InitServo();
  ConnectWiFi();
  ConnectMQTT();
  RFID_Connect();
  IsPair();
  Subscribe("response/"+WiFi.macAddress());
}

void loop(){
  Loop();
  static unsigned long lastScanTime = 0;
  const unsigned long scanCooldown = 3000; 

  if (millis() - lastScanTime < scanCooldown) {
    return; 
  }

  if (!PICC_IsNewCardPresent() || !PICC_ReadCardSerial()) {
    return;
  }
  Scan();

  lastScanTime = millis(); 
  PICC_HaltA();    
  PCD_StopCrypto1();
}