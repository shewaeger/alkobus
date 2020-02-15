//
// Created by shewa on 07.02.2020.
//

#include "AlkobusMenu.h"
#include <list_utils.h>
#include <LiquidCrystal_I2C.h>
#include <Program.h>
#include <Arduino.h>

#define CURSOR_CHAR ((char)0x7e)
#define  OFFSET_TIME 800

AlkobusMenu::AlkobusMenu(LiquidCrystal_I2C *lcd):
        lcd(lcd),
        selector(0),
        items(NULL),
        selectorPos(0),
        countProgram(0),
        currentOffset(0),
        lastOffsetTime(millis()){
    lcd->clear();
}

void AlkobusMenu::addProgram(Program *program) {
    push_list_element(&this->items, &program, sizeof(Program *));
    this->countProgram = count_list(this->items);
}

void AlkobusMenu::selectorDown() {
    if(selector >= countProgram - 1){
        selector = countProgram - 1;
        return;
    }
    selector++;
    selectorPos = 1;
    currentOffset = 0;
    lastOffsetTime = millis();
}

void AlkobusMenu::selectorUp() {
    if(selector <= 0){
        selector = 0;
        return;
    }
    selector--;
    selectorPos = 0;
    currentOffset = 0;
    lastOffsetTime = millis();
}

void AlkobusMenu::setSelector(size_t selector) {
    this->selector = selector;
}

Program *AlkobusMenu::getCurrentProgram() {
    return *(Program **) get_list_element(items, selector);
}

void AlkobusMenu::redrawScreen() {
    lcd->setCursor(0, selectorPos);
    lcd->print(CURSOR_CHAR);
    lcd->setCursor(0, !selectorPos);
    lcd->print(" ");
    if(selectorPos){
        Program *p;
        if(selector != 0) {
             p = *(Program **) get_list_element(items, selector - 1);
            printProgram(0, p, 0);
        }
        p =  *(Program **)get_list_element(items, selector);
        printProgram(1, p, currentOffset);
    } else {
        Program *p = *(Program **)get_list_element(items, selector);
        printProgram(0, p, currentOffset);
        if(selector != countProgram - 1 ){
            p = *(Program **) get_list_element(items, selector + 1);
            printProgram(1, p, 0);
        }
    }
}

AlkobusMenu::~AlkobusMenu() {
    while(this->items) {
        Program * p = *(Program **)get_list_element(items, 0);
        delete p;
        remove_list_element(&items, 0);
    }
}

void AlkobusMenu::printProgram(size_t position, Program *p, size_t offset) {
    lcd->setCursor(1, position);
    size_t nameLength = strlen(p->getName());
    if(nameLength > 15){
        lcd->print(p->getName() + offset);
        if(offset >= nameLength - 15)
            lcd->print('*');
    }
    else {
        int spacelen = 15 - nameLength ;
        lcd->print(p->getName());
        while(spacelen--)
            lcd->print(" ");
    }

}

void AlkobusMenu::loop() {
    size_t offsetTime = OFFSET_TIME;
    size_t nameLength = strlen(getCurrentProgram()->getName());
    if(currentOffset == 0 || currentOffset == nameLength - 14)
        offsetTime+= OFFSET_TIME*2;

    if(millis() - lastOffsetTime >offsetTime){
        currentOffset++;
        if(currentOffset == nameLength - 13) {
            currentOffset = 0;
        }
        lastOffsetTime = millis();
    }
    redrawScreen();
}
