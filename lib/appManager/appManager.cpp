#include "appManager.h"
#include <WiFi.h>

#define MODE_BUTTON_PIN 14
#define SELECT_BUTTON_PIN 27
#define UP_BUTTON_PIN 16
#define DOWN_BUTTON_PIN 17
#define BUZZER_PIN 13


WifiConnect wifi;
Alarm alarmClock;
PomodoroManager pomodoro;

AppManager :: AppManager():
    modeButton(MODE_BUTTON_PIN),
    selectButton(SELECT_BUTTON_PIN),
    upButton(UP_BUTTON_PIN),
    downButton(DOWN_BUTTON_PIN),
    buzzer(BUZZER_PIN,25){

        activeApp = AppType :: ALARM;
    }

void AppManager :: begin(){

    pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
    pinMode(DOWN_BUTTON_PIN,INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);

    wifi.connect();

    rtc.connectNtp();
    alarmClock.setAlarm(8,0);
    pomodoro.setUpSession(4,60*1000*60,60*1000*10);
}

void AppManager :: update(){
    switch(activeApp){
        case AppType :: POMODORO:
            pomodoro.update();
            pomodoro.printStates();
        break;
        case AppType :: ALARM:
            alarmClock.update();
            if(alarmClock.getIsActive() == true){
                buzzer.powerUp();
            }
            //turn off when the alarm hour passed
            if (alarmClock.getIsActive() == false){
                buzzer.powerDown();
            }
        break;
    }
}

void AppManager :: handleInput(){
    modeButton.update();
    selectButton.update();
    upButton.update();
    downButton.update();

    //button control for modeButton
    if(modeButton.wasPressed()){    
        Serial.print("MODE CHANGED TO:");
        switch(activeApp){
            case AppType :: POMODORO:
                activeApp = AppType::ALARM;
                Serial.print("ALARM");
            break;
            case AppType :: ALARM:
                activeApp = AppType :: POMODORO;
                Serial.print("POMODORO");
            break;
        }

    //button control for selectButton
    }else if(selectButton.wasPressed()){
        switch(activeApp){
            case AppType :: POMODORO:
                pomodoro.buttonStartPause();
            break;
            case AppType :: ALARM:
                alarmClock.stop();
            break;
        }
    
    //button control for upButton       
    }else if(upButton.wasPressed()){
        switch(activeApp){
            case AppType :: POMODORO:
                pomodoro.buttonStartPause();
            break;
            case AppType :: ALARM:
                alarmClock.stop();
            break;
        }

    //button control for downButton
    }else if(downButton.wasPressed()){
        switch(activeApp){
            case AppType :: POMODORO:
                pomodoro.buttonSkip();
            break;
            case AppType :: ALARM:
                alarmClock.snooze();
            break;
        }
    }
}