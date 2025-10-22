#include "sound.h"
#include <Arduino.h>

int pin;
unsigned long durationMs;
unsigned long lastPowerUpTimeLog;

Sound :: Sound(int pin){
    this->pin = pin;
}

void Sound :: powerUp(){
    digitalWrite(pin, HIGH);
    lastPowerUpTimeLog = millis();
}

void Sound :: powerDown(){
    digitalWrite(pin, LOW);
}

void Sound :: setSoundIntervalMs(unsigned long intervalMs){
    durationMs = intervalMs;
}

bool Sound :: intervalPassed(){
    return (millis() - lastPowerUpTimeLog) >= durationMs; 
}

void Sound :: powerDownAfterInterval(){
    if(intervalPassed() == true){
        powerDown();
    }
}

void Sound :: powerUpAfterInterval(){
    if(intervalPassed() == true){
        powerUp();
    }
}

