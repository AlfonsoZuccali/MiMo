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
        rtc.SetDateTime(compiled);
    }

    if (rtc.GetIsWriteProtected()) {
        rtc.SetIsWriteProtected(false);
    }

    if (!rtc.GetIsRunning()) {
        rtc.SetIsRunning(true);
    }

    RtcDateTime now = rtc.GetDateTime();
    if (now < compiled) {
        rtc.SetDateTime(compiled);
    }
}


RtcDateTime RtcClock :: getDateTime(){
    return  rtc.GetDateTime();
}