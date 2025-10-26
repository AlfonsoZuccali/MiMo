#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <time.h>
#include "sound.h"
#include "countdown.h"
#include "pomodoroManager.h"
#include "button.h"
#include "clock.h"
#include "wifiConnect.h"
#include "alarm.h"

//define pins
#define FOCUS_PIN 26
#define REST_PIN 25
#define IDLE_PIN 33
#define SKIP_PIN 27
#define START_PIN 14
#define BUZZER_PIN 13

//set input and output objects
Button skip(SKIP_PIN,50);
Button start(START_PIN,50);
Sound Buzzer(BUZZER_PIN, 25);

//initialize our Pomodoro
PomodoroManager Gestor;
pomodoroStatus lastState;

WifiConnect wifi;

Clock realTimeClock;

Alarm wakeUp;

//set pomodoro settings
int rounds = 3;
unsigned long focusTimeMs = 5*1000;
unsigned long restTimeMs = 5*1000;
unsigned long lastTimeLog;




void setup() {

    Serial.begin(115200);
    
    //set pins
    pinMode(FOCUS_PIN, OUTPUT);
    pinMode(REST_PIN, OUTPUT);
    pinMode(IDLE_PIN, OUTPUT);
    pinMode(SKIP_PIN,INPUT_PULLUP);
    pinMode(START_PIN,INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);

    //set up rtc
    //set up the pomodoro
    Gestor.setUpSession(rounds,focusTimeMs,restTimeMs);

    wifi.connect();
    realTimeClock.connectNtp();
    wakeUp.setAlarm(6,30);
}
void loop() {
    //update the wakeUp alarm status
    wakeUp.update();
    start.update();
    skip.update();

    if(skip.wasPressed() == true){
        wakeUp.snooze();
    }

    if(start.wasPressed() == true){
        wakeUp.stop();
    }

    //sound if its time to wake up
    if(wakeUp.getIsActive() == true){
        Buzzer.powerUp();
    }


    //turn off when the alarm hour passed
    if (wakeUp.getIsActive() == false){
        Buzzer.powerDown();
    }

    /*
    //check the buttons states
    start.update();
    skip.update();
 
    //sync led and pomodoro status
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

    //we store the state of the pomodoro before updating it
    lastState = Gestor.getState();
    Gestor.update();
    */
}