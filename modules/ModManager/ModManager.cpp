//
// Created by shewa on 19.10.19.
//

#include "ModManager.h"

ModManager *ModManager::manager = NULL;

ModManager *ModManager::getManager() {
    if (manager == NULL)
        manager = new ModManager();
    return manager;
}

ModManager::ModManager() {
    this->eventBus = new EventBus();
    this->temperature = new Temperature(10, this->eventBus);
    this->voltageControl = new VoltageControl();
    this->keyboard = new Keyboard(22, 24, 26, 28, 30, this->eventBus);
}

void ModManager::setup() {
    this->temperature->setup();
    this->voltageControl->setup();
    this->keyboard->setup();
}

void ModManager::loop() {
    this->temperature->loop();
    this->voltageControl->loop();
    this->keyboard->loop();
}

EventBus *ModManager::getEventBus() {
    return this->eventBus;
}
