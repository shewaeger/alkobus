//
// Created by shewa on 21.10.19.
//

#include "MainMenu.h"
#include <Arduino.h>
#include <ModManager.h>
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>

MainMenu::MainMenu() : Program() {

}

MainMenu::~MainMenu() {

}

void MainMenu::backgroundLoop() {
    Program::backgroundLoop();
}

void MainMenu::setup() {

}

void MainMenu::loop() {

}

char *MainMenu::getName() {
    return "Главное меню";
}

void MainMenu::event(Event *event) {
    if(event->type == TEMPERATURE_UPDATE_EVENT)
        return;
    LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
    lcd->clear();
    lcd->setCursor(0,0);
    switch (event ->type){
        case SHORT_PUSH_KEY_EVENT:
        case LONG_PUSH_KEY_EVENT:
            switch (*((uint8_t *)event->data)){
                case BUTTON_LEFT:
                    lcd->print("Button left");
                    break;
                case BUTTON_RIGHT:
                    lcd->print("Button right");
                    break;
                case BUTTON_DOWN:
                    lcd->print("Button down");
                    break;
                case BUTTON_UP:
                    lcd->print("Button up");
                    break;
                case BUTTON_OK:
                    lcd->print("Button ok");
                    break;
            }
    }

}

