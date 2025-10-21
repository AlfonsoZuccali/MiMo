#include "button.h"

Button::Button(int pin, unsigned long debounce_ms) {
    this->pin = pin;
    debounce_ms = debounce_ms;
    
    // Initilize pin as pullup
    pinMode(this->pin, INPUT_PULLUP);

    // establish intial states
    lastSteadyState = HIGH; 
    lastFlickerableState = HIGH;
    lastDebounceTime = 0;
    wasPressedFlag = false;
}

void Button::update() {
    int currentState = digitalRead(pin);

    // debounce logic
    //if the current state isnt equal to the last unstable state 
    if (currentState != lastFlickerableState) {
        //we record the last time the button detected a press
        lastDebounceTime = millis();
        //we change the last unstable state to the one detected
        lastFlickerableState = currentState;
    }

    //if the "unstable" state was maintained longer than our parameter
    //that probably means it has been pressed
    if ((millis() - lastDebounceTime) > debounce_ms) {
        //then if the state changed
        if (currentState != lastSteadyState) {
            //if the state is low, it means we pressed the button
            if (currentState == LOW) {
                //we pull up the flag
                wasPressedFlag = true;
            }
            //current state will be saved as last steady state
            lastSteadyState = currentState;
        }
    }
}

bool Button::wasPressed() {
    // checks if the flag is up
    if (wasPressedFlag) {
        // it is up, we pull it down and return true
        wasPressedFlag = false; 
        return true;
    }
    // if it isnt we return false
    return false;
}

bool Button::isPressed() {
    //it returns the curren stable state
    //in pullup, low means pressed
    return (lastSteadyState == LOW);
}