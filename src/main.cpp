#include <Arduino.h>
#include <PubSubClient.h>
#include <RtcDS1302.h>
#include "sound.h"
#include "countdown.h"
#include "pomodoroManager.h"
#include "button.h"
#include "clock.h"

//define pins
#define FOCUS_PIN 26
#define REST_PIN 25
#define IDLE_PIN 33
#define SKIP_PIN 27
#define START_PIN 14
#define BUZZER_PIN 13

#define DATA 21
#define CLOCK 22
#define CLOCK_RESET 19

//set input and output objects
Button skip(SKIP_PIN,50);
Button start(START_PIN,50);
Sound Buzzer(BUZZER_PIN, 25);
RtcClock rtc(DATA,CLOCK,CLOCK_RESET);

//initialize our Pomodoro
PomodoroManager Gestor;
pomodoroStatus lastState;

//set pomodoro settings
int rounds = 3;
unsigned long focusTimeMs = 5*1000;
unsigned long restTimeMs = 5*1000;
unsigned long lastTimeLog;



void setup() {

    Serial.begin(9600);
    
    //set pins
    pinMode(FOCUS_PIN, OUTPUT);
    pinMode(REST_PIN, OUTPUT);
    pinMode(IDLE_PIN, OUTPUT);
    pinMode(SKIP_PIN,INPUT_PULLUP);
    pinMode(START_PIN,INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);

    //set up rtc
    rtc.begin();

    //set up the pomodoro
    Gestor.setUpSession(rounds,focusTimeMs,restTimeMs);


}
void loop() {
    //check the buttons states
    start.update();
    skip.update();
    rtc.printDateTime(rtc.getDateTime());

    //if-statements for button feedback, sound and pomodoro actions
    if(start.wasPressed() == true){
        Gestor.buttonStartPause();
        Buzzer.powerUp();

    }else if(skip.wasPressed() == true){
        Gestor.buttonSkip();
        Buzzer.powerUp();
    }
    
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

    //if the state changed, the buzzer will sound
    if(lastState != Gestor.getState()){
        Buzzer.powerUp();
    }
    Buzzer.powerDownAfterInterval();
}