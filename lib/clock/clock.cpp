#include "clock.h"
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Arduino.h>

RtcClock :: RtcClock(int dataPin, int clockPin, int resetPin):
        // Construct the wire object by passing the pins
        wire(dataPin, clockPin, resetPin), 
        // Construct the rtc object by passing the wire object
        rtc(wire) 
{
}

void RtcClock :: begin(){
    //initialice rtc
    rtc.Begin();

    //record current time
    RtcDateTime compiled = RtcDateTime(__DATE__,__TIME__); 

    //checking if the rtc is functioning correctly
    if (!rtc.IsDateTimeValid()) {
            Serial.println("RTC lost confidence in the DateTime!");
        rtc.SetDateTime(compiled);
    }

    if (rtc.GetIsWriteProtected()) {
            Serial.println("RTC was write protected, enabling writing now");
        rtc.SetIsWriteProtected(false);
    }

    if (!rtc.GetIsRunning()) {
            Serial.println("RTC was not actively running, starting now");
        rtc.SetIsRunning(true);
    }

    RtcDateTime now = rtc.GetDateTime();
    if (now < compiled) {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        rtc.SetDateTime(compiled);
    } else if (now > compiled) {
        Serial.println("RTC is newer than compile time. (this is expected)");
    } else if (now == compiled) {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}


RtcDateTime RtcClock :: getDateTime(){
    return  rtc.GetDateTime();
}

void RtcClock :: printDateTime(const RtcDateTime& dt) {
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second());
  Serial.println(datestring);
}