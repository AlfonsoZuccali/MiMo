#include "clock.h"
#include <time.h>
#include <Arduino.h>

Clock :: Clock(){}

void Clock :: connectNtp(){

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    setenv("TZ","<-03>3",1);
    tzset();
}

void Clock :: printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
