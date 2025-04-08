#include <ESP32Servo.h>

#define Servo_PIN 25

Servo ServoMoteur;
bool Open = false;

void InitServo(){
    ServoMoteur.setPeriodHertz(50);
    ServoMoteur.attach(Servo_PIN, 500, 2400);
}

bool OpenLocker(){
    if (Open){
        Serial.println("Coffre deja ouvert");
        return false;
    }
    Serial.println("Ouverture...");
    for (int pos = 0; pos <= 180; pos += 1) {
        ServoMoteur.write(pos);
        delay(10);
    }
    Open = true;
    return true;
}

bool CloseLocker(){
    if (!Open){
        Serial.println("Coffre deja fermé");
        return false;
    }
    Serial.println("Fermeture...");
    for (int pos = 180; pos >= 0; pos -= 1) {
        ServoMoteur.write(pos);
        delay(10);
    }
    Open = false;
    return true;
}
bool IsOpen(){
    return Open;
}