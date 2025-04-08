#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include <PubSubClient.h>
#include "Servo/Servo.hpp"

#define RED_LED 26
#define GREEN_LED 27

const char* password = "TartelettE";
const char* ssid = "Moi";


WiFiClient wifiClient;
PubSubClient client(wifiClient);

void ConnectWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  
  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void GetMessage(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] "); 
  Serial.println("");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  if ((char)payload[0] == 't' && (char)payload[1] == 'r'&& (char)payload[2] == 'u'&& (char)payload[3] == 'e')
  {
    Serial.println("on");
    digitalWrite(GREEN_LED, HIGH);
    delay(600);
    digitalWrite(GREEN_LED, LOW);

  }else if ((char)payload[0] == 'f' && (char)payload[1] == 'a'&& (char)payload[2] == 'l'&& (char)payload[3] == 's'&& (char)payload[4] == 'e')
  {
    Serial.println("off");
    digitalWrite(RED_LED, HIGH);
    delay(600);
    digitalWrite(RED_LED, LOW);
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
  Serial.println("message send");
}

void Loop(){
  client.loop();
}