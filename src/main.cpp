#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <time.h>
#include "sound.h"
#include "countdown.h"
#include "pomodoroManager.h"
#include "button.h"
#include "clock.h"
#include "wifiConnect.h"
#include "alarm.h"
#include "appManager.h"
#include "spotify.h"

    AppManager OS;

void setup() {
    Serial.begin(115200);
    OS.begin();

}
void loop() {
    OS.update();
    OS.handleInput();
    
}