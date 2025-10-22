#ifndef SOUND_H
#define SOUND_H


class Sound{

    public:
        Sound(int pin);

        void setSoundIntervalMs(unsigned long interval);
        void duringInterval();
        void powerUp();
        void powerDown();
        void powerDownAfterInterval();
        void powerUpAfterInterval();

    private:
        unsigned long durationMs;
        int pin;
        unsigned long lastPowerUpTimeLog;

        bool intervalPassed();
};

#endif