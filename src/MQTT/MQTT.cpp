#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include <PubSubClient.h>
#include "Servo/Servo.hpp"

#define RED_LED 26
#define GREEN_LED 27


WiFiClient wifiClient;
PubSubClient client(wifiClient);

void GetMessage(char* topic, byte* payload, unsigned int length){
  Serial.print("[" + String(topic) + "]");
  String message = String((char*)payload).substring(0, length);
  Serial.println(message);

  if (message == "allowed"){
    digitalWrite(GREEN_LED, HIGH);
    OpenLocker();
    delay(600);
    digitalWrite(GREEN_LED, LOW);
  }else if (message == "denied"){
    digitalWrite(RED_LED, HIGH);
    delay(600);
    digitalWrite(RED_LED, LOW);
  }else if (message == "close"){
    CloseLocker();
  }else if (message == "green"){
    digitalWrite(GREEN_LED, HIGH);
    delay(600);
    digitalWrite(GREEN_LED, LOW);
  }else {
    Serial.println("Message inconnu");
  }
  return;
}

void ConnectMQTT(){
  client.setServer("10.33.75.211", 1883);
  client.setCallback(GetMessage);
  client.connect("ESP32_clientID");
  {
    Serial.println("connected to MQTT");
    if (!client.connected())
    {
      ConnectMQTT();
    }
  }
}

void Subscribe(String topic){
  client.subscribe(topic.c_str());
}

void SendMessage(String message,String topic){
  client.publish(topic.c_str(),message.c_str());
}

void Loop(){
  client.loop();
}
void IsPair(){
  SendMessage(WiFi.macAddress(),"pair");
}