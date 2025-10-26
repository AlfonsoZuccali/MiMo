#include <Arduino.h>
#include <time.h>
#include "alarm.h"
#include "clock.h"
#include "sound.h"

Alarm :: Alarm(){
    enabled = false;
    isActive = false;
    stopped = false;
}

void Alarm :: setAlarm(int hour, int minute){
    this->hour = hour;
    this->minute = minute;
    enabled = true;
}

void Alarm :: update(){

    if(enabled == false){
        return;
    }

    if(snoozed == true){
        if((millis() - snoozeStartTime) >= snoozeDuration){
            snoozed = false;
            isActive = true;
        }else{
            return;
        }
    }

    struct tm timeinfo;
    
    if (!getLocalTime(&timeinfo)) {
      return;
    }

    if(timeinfo.tm_hour == hour && timeinfo.tm_min == minute){
        if(isActive == false && stopped == false){
            isActive = true;
        }
    }else{
        stopped = false;
    }
}

void Alarm :: stop(){
    if(isActive == true){
        isActive = false;
        stopped = true;
    }else{
        return;
    }
}

void Alarm :: snooze(){
    if(isActive == true){
        isActive = false;
        snoozed = true;
        snoozeStartTime = millis();
    }else{
        return;
    }
}

bool Alarm :: getIsActive(){
    return isActive;
}

