#include <Arduino.h>
#include <time.h>
#include "alarm.h"
#include "clock.h"

Alarm :: Alarm(){
    //set everything to false until alarm is set
    enabled = false;
    isActive = false;
    stopped = false;
}

void Alarm :: setAlarm(int hour, int minute){
    //get the alarm set and enabled
    this->hour = hour;
    this->minute = minute;
    enabled = true;
}

void Alarm :: update(){
    if(enabled == false){
        return;
    }

    //set behavior for the snooze state
    if(snoozed == true){
        if((millis() - snoozeStartTime) >= snoozeDuration){
            snoozed = false;
            isActive = true;
        }else{
            return;
        }
    }

    //struct that will contain the time information
    struct tm timeinfo;
    
    //in case we cant synchronize the time
    if (!getLocalTime(&timeinfo)) {
      return;
    }

    //logic for activating in the set time
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

