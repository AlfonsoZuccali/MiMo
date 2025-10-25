#include <WiFi.h>
#include <time.h>
#include "wifiConnect.h"

WifiConnect :: WifiConnect(){
}

void WifiConnect :: connect(){
    WiFi.begin(this->ssid,this->password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
    }
     Serial.println("WiFi connected.");
}

void WifiConnect :: disconnect(){
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}
