#ifndef CLOCK_H
#define CLOCK_H
#include <time.h>
#include <Arduino.h>

class Clock{
    public:
        //constructor  
        Clock();
        void connectNtp();
        void printLocalTime();
        String getFormattedDateTime();

    private:
        //for connecting ntp
        const char* ntpServer = "pool.ntp.org";
        const long  gmtOffset_sec = 3;
        const int   daylightOffset_sec = 3600;
};
#endif