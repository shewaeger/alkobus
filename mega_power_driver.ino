#include <Arduino.h>
#include "User_Setup.h"
#include <ModManager.h>

#include <ProgramManager.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Starting....");
    ModManager *manager = ModManager::getManager();
    manager->setup();
    Serial.println("Started.");
    ProgramManager::getManager()->setup();

}

void loop() {
    ModManager::getManager()->loop();
    ProgramManager::getManager()->loop();
}