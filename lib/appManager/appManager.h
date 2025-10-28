#ifndef APPMANAGER_H
#define APPMANAGER_H

#define MODE_BUTTON_PIN 27
#define SELECT_BUTTON_PIN 14
#define UP_BUTTON_PIN 16
#define DOWN_BUTTON_PIN 17

#include "button.h"
#include "pomodoroManager.h"
#include "clock.h"
#include "alarm.h"

enum class AppType{
    POMODORO, ALARM, CLOCK
};

class AppManager{
    public:
        AppManager();

        void begin();
        void switchApp();
        void update();
        void handleInput();
    
    private:
        AppType activeApp;

        Button modeButton(int pin);
        Button selectButton(int pin);
        Button upButton(int pin);
        Button downButton(int pin);

        PomodoroManager pomodoro;
        Alarm clockAlarm;
};


#endif