//
// Created by shewa on 21.10.19.
//

#include "MainMenu.h"
#include <ModManager.h>
#include <LiquidCrystal_I2C.h>

MainMenu::MainMenu() : Program() {

}

MainMenu::~MainMenu() {

}

void MainMenu::backgroundLoop() {
    Program::backgroundLoop();
}

void MainMenu::setup() {
    Program::setup();
}

void MainMenu::loop() {
    Program::loop();
}

void MainMenu::event(Event *event) {
    Program::event(event);
}

void MainMenu::exit() {
    Program::exit();
}
