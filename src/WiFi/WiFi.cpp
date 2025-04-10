#include <WiFiManager.h>

WiFiManager wm;

void ConnectWiFi(){
    wm.autoConnect("Locker","");
}