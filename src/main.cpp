#include <Arduino.h>
#include <PubSubClient.h>
#include "countdown.h"
#include "pomodoroManager.h"
#include <string.h>

#define BUTTON_SKIP 17
#define BUTTON_START_PAUSE 15

PomodoroManager miGestor;
pomodoroStatus ultimo_estado;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  pinMode(BUTTON_SKIP,INPUT_PULLUP);
}

void loop() {
  int skip =digitalRead(BUTTON_SKIP);
    Serial.write(skip);
}
