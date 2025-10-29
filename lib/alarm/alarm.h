#ifndef ALARM_H
#define ALARM_H
#include <time.h>
#include "clock.h"

class Alarm{


    public:
        Alarm();
        //sets the alarm with hour and minute
        void setAlarm(int hour, int minute);
        bool isEnabled();
        void stop();
        void snooze();
        //responsible for updating the values of the alarm on each loop iteration
        void update();
        bool getIsActive();
    

    private:
        Clock rtc;
        int hour;
        int minute;
        bool enabled;
        bool snoozed;
        //to prevent activating multiple times in the same minute
        bool isActive;
        bool stopped;
        unsigned long snoozeStartTime;
        const unsigned long snoozeDuration = 2*60*1000;


};

#endif