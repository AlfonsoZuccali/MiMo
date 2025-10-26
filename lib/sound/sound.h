#ifndef SOUND_H
#define SOUND_H


class Sound{

    public:
        //constructor
        Sound(int pin, unsigned long intervalMs);

        //powers Up the sound pin and records the time when it happened in "lastPowerUpTimeLog"
        void powerUp();

        //powers down the sound pin
        void powerDown();

        //turns off power from the sound pin after the interval set in constructor
        void powerDownAfterInterval(unsigned long duration);

        //turns on power from the sound pin after the interval set in constructor
        void powerUpAfterInterval(unsigned long duration);

        //to change interval without having to make another object
        void setInterval(unsigned long duration);

    private:
        unsigned long durationMs;
        int pin;
        unsigned long lastPowerUpTimeLog;

        bool intervalPassed(unsigned long duration, unsigned long lastPower);
        unsigned long getDurationMs();
};

#endif