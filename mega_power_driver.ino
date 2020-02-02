#include <Arduino.h>
#include "User_Setup.h"
#include <ModManager.h>
#include <MainMenu.h>

#include <ProgramManager.h>
#include <Valve.h>
void setup() {
    Serial.begin(9600);
    Serial.println("Starting....");
    ModManager::getManager()->setup();
    ProgramManager::getManager()->setup();
    Serial.println("Started.");
}

void loop() {
    ModManager::getManager()->loop();
    ProgramManager::getManager()->loop();
}
