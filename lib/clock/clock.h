#ifndef CLOCK_H
#define CLOCK_H
#include <ThreeWire.h>
/*ThreeWire es un software que simula un protocolo de comunicación
 específico usando tres pines de propósito general, 
 permitiendo que bibliotecas de más alto nivel (como la del RTC) 
 puedan hablar con hardware que no usa protocolos estándar.*/
#include <RtcDS1302.h>
#include <Arduino.h>

class RtcClock{
    public:
        //constructor  
        RtcClock(int dataPin, int clockPin, int resetPin);
        //initializes the clock
        void begin();
        //returns the date and time
        RtcDateTime getDateTime();
    private:
        ThreeWire wire;
        RtcDS1302<ThreeWire> rtc;
};
#endif