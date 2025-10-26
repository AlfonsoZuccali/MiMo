#include "clock.h"
#include <time.h>
#include <Arduino.h>

Clock :: Clock(){}

void Clock :: connectNtp(){

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  setenv("TZ","<-03>3",1);
  tzset();
}

void Clock :: printLocalDateTime(){
  //Create a structure to store time information
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


String Clock::getFormattedDateTime() {
    // 1. Create a structure to store time information
    struct tm timeinfo;

    // 2. Try to get the local time. If not yet synchronized, return a message
    if (!getLocalTime(&timeinfo)) {
      return "Synchronizing..";
    }

    // 3. Create a buffer to write the text
    char buffer[25];

    // 4. Use snprintf() to format the time from the 'timeinfo' structure
    //    NOTE THE CORRECTIONS! The year is since 1900 and the month is 0-11.
    snprintf(buffer, sizeof(buffer),
         "%02u/%02u/%04u %02u:%02u:%02u",
         timeinfo.tm_mday,
         timeinfo.tm_mon + 1,      // Add 1 to the month
         timeinfo.tm_year + 1900,  // Add 1900 to the year
         timeinfo.tm_hour,
         timeinfo.tm_min,
         timeinfo.tm_sec);

    // 5. Convert the buffer to a String and return it
    return String(buffer);
}
