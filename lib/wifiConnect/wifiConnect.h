#ifndef WIFICONNECT_H
#define WIFICONNECT_H
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
        const char* ssid = "***REMOVED***";
        const char* password = "***REMOVED***";



};

#endif