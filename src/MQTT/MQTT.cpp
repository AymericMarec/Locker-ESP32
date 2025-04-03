#include <WiFi.h>
#include <ArduinoMqttClient.h>

const char* password = "TartelettE";
const char* ssid = "Moi";

const char broker[] = "10.33.75.220";
int        port     = 1883;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

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

void ConnectMQTT(){
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}


void SendMessage(char message[],char topic[]){
  mqttClient.beginMessage(topic);
  mqttClient.print(message);
  mqttClient.endMessage();
  Serial.println("message send");
}

void Subscribe(char topic[]){
  mqttClient.subscribe(topic);
}

void ListenMessage(){
  mqttClient.poll();
  if (mqttClient.available()) {
    String Message;
    while (mqttClient.available()) {
        Message += (char)mqttClient.read();
    }
    Serial.println(Message);
  } 
}
  // mqttClient.poll();
  // if (mqttClient.parseMessage()){
  //   Serial.print("Message reçu sur ");
  //   Serial.println(mqttClient.messageTopic());
  //   Serial.print("Contenu du message : ");
  //   while (mqttClient.available()) {
  //     Serial.print((char)mqttClient.read());
  //   }
  //   Serial.println();
  // }