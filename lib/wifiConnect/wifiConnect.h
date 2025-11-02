#ifndef WIFICONNECT_H
#define WIFICONNECT_H
#include "../credentials.h"
#include <WiFi.h>
#include <time.h>
#include <Arduino.h>

class WifiConnect{
    public:
        WifiConnect();
        void connect();
        void disconnect();
        void connectNtp();

    private:
        const char* ssid = SSID;
        const char* password = PASSWORD;
};
#endif