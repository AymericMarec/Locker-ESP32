#include <Arduino.h>
#define LED1 2
#include <WiFi.h>

const char* password = "TartelettE";
const char* ssid = "Moi";

void setup() {
  Serial.begin(9600);
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
void loop(){

}