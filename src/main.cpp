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
  SendMessage("ntm max");

  
}
void loop(){
  if ( ! PICC_IsNewCardPresent()) {
    return;
 }

 if ( ! PICC_ReadCardSerial()) {
    return;
 }

 Serial.println(GetUID());
}