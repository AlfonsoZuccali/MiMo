#include "clock.h"
#include <time.h>
#include <Arduino.h>

Clock :: Clock(){}

void Clock :: connectNtp(){

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    setenv("TZ","<-03>3",1);
    tzset();
}

void Clock :: printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


String Clock::getFormattedDateTime() {
    // 1. Crea una estructura para guardar la información del tiempo
    struct tm timeinfo;

    // 2. Intenta obtener la hora local. Si no está sincronizado aún, devuelve un mensaje
    if (!getLocalTime(&timeinfo)) {
        return "Sincronizando hora...";
    }

    // 3. Crea un "lienzo" o buffer para escribir el texto
    char buffer[25];

    // 4. Usa snprintf() para formatear la hora desde la estructura 'timeinfo'
    //    ¡OJO A LAS CORRECCIONES! El año es desde 1900 y el mes es 0-11.
    snprintf(buffer, sizeof(buffer),
             "%02u/%02u/%04u %02u:%02u:%02u",
             timeinfo.tm_mday,
             timeinfo.tm_mon + 1,      // Se le suma 1 al mes
             timeinfo.tm_year + 1900,  // Se le suman 1900 al año
             timeinfo.tm_hour,
             timeinfo.tm_min,
             timeinfo.tm_sec);

    // 5. Convierte el buffer a un String y lo devuelve
    return String(buffer);
}