#ifndef MQTT_HPP
#define MQTT_HPP

void ConnectWifi();
void ConnectMQTT();
void SendMessage(String message,char topic[]);
void Subscribe(char topic[]);
void ListenMessage();

#endif