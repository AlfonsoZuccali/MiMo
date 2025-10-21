#include "countdown.h"
#include <Arduino.h>

Countdown :: Countdown(){
    //when starting the countdown, everything is set to 0
    reset(); 
}

void Countdown :: start(unsigned long durationMs){
    //to avoid starting when it already has
    if(isFinished() == true || running == false){
        this->durationMs = durationMs;
        this->startTimeMs = millis();
        this->elapsedTimeBeforePause = 0;
        this->running = true;
    }
}

void Countdown :: reset(){
    this->startTimeMs = 0;
    this->durationMs = 0;
    this->elapsedTimeBeforePause = 0;
    this->running = false;
}

void Countdown :: resume(){
    //you can only resume if it is paused
    if(this->running == false){
        //the difference between the two points will return when was the last
        //moment before pause
        this->startTimeMs = millis() - elapsedTimeBeforePause;
        this->running = true;
    }
}

void Countdown :: pause(){
    // Record the time already elapsed since the countdown started:
    this->elapsedTimeBeforePause = millis() - startTimeMs;
    // Mark the countdown as not running so future calls know it's paused.
    this->running = false;
}

unsigned long Countdown :: getRemainingTime(){
    // If the countdown is currently running, calculate remaining time as:
    // duration minus time elapsed since start.
    if(running == true){
        return durationMs - (millis() - startTimeMs);
    
    }
    // If the countdown is paused
    return durationMs - elapsedTimeBeforePause;
}

bool Countdown :: isFinished(){
    // Return true when the elapsed time since the (adjusted) start time
    // is greater than or equal to the configured duration.
    if(running == true){
        return (millis() - startTimeMs) >= durationMs;
    }else{
        return false;
    }
}

bool Countdown :: isRunning(){
    return running;
}


