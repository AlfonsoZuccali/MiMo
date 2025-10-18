#ifndef COUNTDOWN_H
#define COUNTDOWN_H

class Countdown{
    public:
        Countdown(); //constructor
        
        // Starts the countdown when given a value
        void start(unsigned long durationMs);
        //Detects wether the countdows is running and in case it is not, it resumes it
        void resume();
        //Pauses the countdown if is running
        void pause();
        //Resets all values to zero
        void reset();
        //Evaluates if the timer finished
        bool isFinished();
        unsigned long getRemainingTime();
        bool isRunning();
    
    private:
        //it stores when the countdown started
        unsigned long startTimeMs;
        //it stores the total duration of the countdown
        unsigned long durationMs;
        //it stored how much time was spent before pause
        unsigned long elapsedTimeBeforePause;
        //states if the counter is running
        bool running;
};
#endif