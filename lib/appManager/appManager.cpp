#include "appManager.h"

Alarm alarmClock;
PomodoroManager pomodoro;

AppManager :: AppManager(){

    modeButton(MODE_BUTTON_PIN);
    selectButton(SELECT_BUTTON_PIN);
    upButton(UP_BUTTON_PIN);
    downButton(DOWN_BUTTON_PIN);


    activeApp = AppType :: CLOCK;
}

void AppManager :: begin(){
    alarmClock.setAlarm(6,30);
    pomodoro.setUpSession(4,60*1000*60,60*1000*10);
}