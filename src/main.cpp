#include <Arduino.h>
#include <PubSubClient.h>
#include "countdown.h"
#include "pomodoroManager.h"
#include "button.h"

    #define FOCUS_PIN 26
    #define REST_PIN 25
    #define IDLE_PIN 33
    #define SKIP_PIN 27
    #define START_PIN 14

    Button skip(SKIP_PIN,50);
    Button start(START_PIN,50);

    PomodoroManager Gestor;
    pomodoroStatus lastState;

    int rounds = 3;
    unsigned long focusTimeMs = 5*1000;
    unsigned long restTimeMs = 5*1000;

void setup() {
    pinMode(FOCUS_PIN, OUTPUT);
    pinMode(REST_PIN, OUTPUT);
    pinMode(IDLE_PIN, OUTPUT);
    pinMode(SKIP_PIN,INPUT_PULLUP);
    pinMode(START_PIN,INPUT_PULLUP);

    Gestor.setUpSession(rounds,focusTimeMs,restTimeMs);

    lastState = Gestor.getState();
}
void loop() {
    start.update();
    skip.update();
    if(start.wasPressed() == true){
        Gestor.buttonStartPause();
    }else if(skip.wasPressed() == true){
        Gestor.buttonSkip();
    }

    if(Gestor.getState() == pomodoroStatus :: FOCUS){
        digitalWrite(FOCUS_PIN,HIGH);
        digitalWrite(REST_PIN,LOW);
        digitalWrite(IDLE_PIN,LOW);
    }else if(Gestor.getState() == pomodoroStatus :: REST){
        digitalWrite(FOCUS_PIN,LOW);
        digitalWrite(REST_PIN,HIGH);
        digitalWrite(IDLE_PIN,LOW);
    }else if(Gestor.getState() == pomodoroStatus :: IDLE){
        digitalWrite(FOCUS_PIN,LOW);
        digitalWrite(REST_PIN,LOW);
        digitalWrite(IDLE_PIN,HIGH);
    }
    Gestor.update();
}