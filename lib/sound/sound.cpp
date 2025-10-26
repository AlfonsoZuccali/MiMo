#include "sound.h"
#include <Arduino.h>

int pin;
unsigned long durationMs;
unsigned long lastPowerUpTimeLog;
unsigned long lastPowerDownTimeLog;

Sound :: Sound(int pin, unsigned long intervalMs){
    this->pin = pin;
    this->durationMs = intervalMs;
}

void Sound :: powerUp(){
    digitalWrite(pin, HIGH);
    lastPowerUpTimeLog = millis();
}

void Sound :: powerDown(){
    digitalWrite(pin, LOW);
    lastPowerDownTimeLog = millis();
}

bool Sound :: intervalPassed(unsigned long duration, unsigned long lastPowerLog){
    return (millis() - lastPowerLog) >= duration; 
}

void Sound :: powerDownAfterInterval(unsigned long duration){
    if(intervalPassed(duration, lastPowerUpTimeLog) == true){
        powerDown();
    }
}

void Sound :: powerUpAfterInterval(unsigned long duration){
    if(intervalPassed(duration, lastPowerDownTimeLog) == true){
        powerUp();
    }
}

void Sound :: setInterval(unsigned long duration){
    this->durationMs = duration;
}

unsigned long Sound :: getDurationMs(){
    return this->durationMs;
}