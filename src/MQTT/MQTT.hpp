#ifndef MQTT_HPP
#define MQTT_HPP

void ConnectWifi();
void ConnectMQTT();
void GetMessage(char* topic, byte* payload, unsigned int length);
void ConnectMQTT();
void Subscribe(String topic);
void SendMessage(String message,String topic);
void Loop();
void IsPair();
#endif