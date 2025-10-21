// Button.h

#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
    //Constructor, pin and debounce time as parameter
    Button(int pin, unsigned long debounce_ms = 50);

    //updates
    void update();

    // returns whether the button was pressed one time
    bool wasPressed();

    // returns whether the button is being pressed
    bool isPressed();

private:
    int pin;
    unsigned long debounce_ms;

    int lastSteadyState;
    int lastFlickerableState;
    unsigned long lastDebounceTime;
    
    // flag that helps with internal methods
    bool wasPressedFlag; 
};

#endif