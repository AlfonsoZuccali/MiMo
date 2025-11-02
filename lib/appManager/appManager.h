#ifndef APPMANAGER_H
#define APPMANAGER_H
#include "button.h"
#include "pomodoroManager.h"
#include "clock.h"
#include "alarm.h"
#include "sound.h"
#include "wifiConnect.h"
#include "spotify.h"
#include <Arduino.h>

#define MODE_BUTTON_PIN 14
#define SELECT_BUTTON_PIN 27
#define UP_BUTTON_PIN 16
#define DOWN_BUTTON_PIN 17
#define BUZZER_PIN 13


enum class AppType{
    POMODORO, ALARM, SPOTIFY
};

class AppManager{
    public:
        AppManager();
        //initializes every object
        void begin();
        void switchApp();
        void update();
        void handleInput();
    
    private:
        AppType activeApp;

        Button modeButton;
        Button selectButton;
        Button upButton;
        Button downButton;
        Sound buzzer;

        PomodoroManager pomodoro;
        Alarm clockAlarm;
        Clock rtc;
        SpotifyClient spotify;

};


#endif