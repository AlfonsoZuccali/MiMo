#include <WiFi.h>
#include <time.h>
#include "wifiConnect.h"

WifiConnect :: WifiConnect(){
}

void WifiConnect :: connect(){
    WiFi.begin(this->ssid,this->password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(5);
    }
     Serial.println("WiFi connected.");
}

void WifiConnect :: disconnect(){
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}
