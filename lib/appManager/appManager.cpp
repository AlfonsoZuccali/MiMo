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
SpotifyClient spotify;

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
    spotify.begin();
    //alarmClock.setAlarm(7,0);
    pomodoro.setUpSession(4,60*1000*60,60*1000*10);
}

void AppManager :: update(){
    
    //even if we are not seeeing it, the pomodoro and alarm still runs
    pomodoro.update();
    alarmClock.update();
    switch(activeApp){
        case AppType :: POMODORO:
            pomodoro.printStates();
        break;
        case AppType :: ALARM:
            if(alarmClock.getIsActive() == true){
                buzzer.powerUp();
            }
            //turn off when the alarm hour passed
            if (alarmClock.getIsActive() == false){
                buzzer.powerDown();
            }
        break;
        case AppType :: SPOTIFY:
            //we update the visuals only when we need it
            spotify.update();
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
                activeApp = AppType :: SPOTIFY;
                Serial.print("SPOTIFY");
            break;
            case AppType :: SPOTIFY:
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
            case AppType :: SPOTIFY:
                Serial.println("Paused or play");    
                spotify.playPause();
                
            break;
        }
    
    //button control for upButton       
    }else if(upButton.wasPressed()){
        switch(activeApp){
            case AppType :: POMODORO:
                //pomodoro.buttonStartPause();
            break;
            case AppType :: ALARM:
                //alarmClock.stop();
            break;
            case AppType :: SPOTIFY:
                Serial.println("Next");
                spotify.nextTrack();
                
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
            case AppType :: SPOTIFY:
                Serial.println("Previous");
                spotify.previousTrack();
               
            break;

        }
    }
}