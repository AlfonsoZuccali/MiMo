#include "sound.h"
#include <Arduino.h>

int pin;
unsigned long durationMs;
unsigned long lastPowerUpTimeLog;

Sound :: Sound(int pin, unsigned long intervalMs){
    this->pin = pin;
    this->durationMs =intervalMs;
}

void Sound :: powerUp(){
    digitalWrite(pin, HIGH);
    lastPowerUpTimeLog = millis();
}

void Sound :: powerDown(){
    digitalWrite(pin, LOW);
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