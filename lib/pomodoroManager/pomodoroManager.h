#ifndef POMODOROMANAGER_U
#define POMODOROMANAGER_U
#include "countdown.h"

enum class pomodoroStatus {
    IDLE,      // waiting for session to start
    FOCUS,      
    REST       
};

class PomodoroManager{
    public:
    //it starts a new session, from round 1 with custom times
    void beginSession(int rounds, unsigned long focusTime, unsigned long restTime);
    //pauses, starts or resumes the timer
    void buttonStartPause();
    //it skips the current timer
    void buttonSkip();
    //checks for updates in the pomodoro
    void update();

    private:
    //stores the number of rounds
    int round;
    //stores the objective amount of rounds
    int roundObjective;
    //indicates whether the pomodoro is active and if is in Focus or Rest
    pomodoroStatus currentState;
    //creates its own instance of a timer
    Countdown timer;
    //stores in miliseconds the amount of focus time
    unsigned long focusTimeMs;
    //stores in miliseconds the amount of rest time
    unsigned long restTimeMs;
};

#endif