#include "pomodoroManager.h"
#include <Arduino.h>

int roundObjectiveGlobal;
unsigned long focusTimeMsGlobal;
unsigned long restTimeMsGlobal;

PomodoroManager :: PomodoroManager(){
    this->round = 0;
    this->roundObjective = 0;
    this->currentState = pomodoroStatus :: IDLE;
    this->restTimeMs = 0;
    this->focusTimeMs = 0;
    this->timer.reset();

}

void PomodoroManager :: setUpSession(int rounds, unsigned long focusTime, unsigned long restTime){
    //sets the rounds
    this->roundObjective = rounds;
    roundObjectiveGlobal = rounds;
    this->round = 1;
    //sets the pomodoro status, focus and rest time
    this->focusTimeMs = focusTime;
    focusTimeMsGlobal = focusTime;
    this->restTimeMs = restTime;
    restTimeMsGlobal = restTime;
    this->currentState = pomodoroStatus :: IDLE;
}

void PomodoroManager :: update(){
    //it only updates if a timer finished
    if(timer.isFinished() == true){
        transitionToNextState();
    }
}

void PomodoroManager :: buttonSkip(){
    transitionToNextState();
}

void PomodoroManager :: buttonStartPause(){
    if(currentState == pomodoroStatus ::IDLE){
        this->timer.start(focusTimeMs);
        currentState = pomodoroStatus :: FOCUS;
    }else{ 
        if (this->timer.isRunning() == true){
            this->timer.pause();
        }else{
            this->timer.resume();
        }
    }
}

pomodoroStatus PomodoroManager :: getState(){
    return currentState;
}

void PomodoroManager :: transitionToNextState(){
    //if it passed a focus period, we set a rest period
    if(currentState == pomodoroStatus :: FOCUS){
        this->timer.start(restTimeMs);
        currentState = pomodoroStatus :: REST;

    }else if(currentState == pomodoroStatus :: REST){ //if it was a rest period
        //if it was the last round, we basically end the session
        if(round >= roundObjective ){
            setUpSession(roundObjectiveGlobal,focusTimeMsGlobal,restTimeMsGlobal);
        }else{//if it wasnt the last round, we update the round number and start a new focus period
            round = round + 1;
            timer.start(focusTimeMs);
            currentState = pomodoroStatus :: FOCUS;
        }
    }
}