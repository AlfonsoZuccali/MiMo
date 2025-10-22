#include <Arduino.h>
#include <PubSubClient.h>
#include <RTClib.h>
#include "sound.h"
#include "countdown.h"
#include "pomodoroManager.h"
#include "button.h"

#define FOCUS_PIN 26
#define REST_PIN 25
#define IDLE_PIN 33
#define SKIP_PIN 27
#define START_PIN 14
#define BUZZER_PIN 13

Button skip(SKIP_PIN,50);
Button start(START_PIN,50);

PomodoroManager Gestor;
pomodoroStatus lastState;
Sound Buzzer(BUZZER_PIN);

int rounds = 3;
unsigned long focusTimeMs = 5*1000;
unsigned long restTimeMs = 5*1000;
unsigned long lastTimeLog;
unsigned long interval = 25;

void setup() {
    pinMode(FOCUS_PIN, OUTPUT);
    pinMode(REST_PIN, OUTPUT);
    pinMode(IDLE_PIN, OUTPUT);
    pinMode(SKIP_PIN,INPUT_PULLUP);
    pinMode(START_PIN,INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);

    Gestor.setUpSession(rounds,focusTimeMs,restTimeMs);

    Buzzer.setSoundIntervalMs(50);

}
void loop() {
    start.update();
    skip.update();

    if(start.wasPressed() == true){
        Gestor.buttonStartPause();
        Buzzer.powerUp();

    }else if(skip.wasPressed() == true){
        Gestor.buttonSkip();
        Buzzer.powerUp();
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

    lastState = Gestor.getState();
    Gestor.update();
    if(lastState != Gestor.getState()){
        Buzzer.powerUp();
    }
    Buzzer.powerDownAfterInterval();
}