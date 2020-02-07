//
// Created by shewa on 07.02.2020.
//

#ifndef MEGA_POWER_DRIVER_ALKOBUSMENU_H
#define MEGA_POWER_DRIVER_ALKOBUSMENU_H


#include <stdint-gcc.h>
#include <stddef.h>

struct list_element;
class Program;
class LiquidCrystal_I2C;

class AlkobusMenu {

private:
    list_element *items = NULL;
    LiquidCrystal_I2C *lcd = NULL;
    size_t selector = 0;
    uint8_t selectorPos = 0;
    size_t countProgram;
    uint8_t currentOffset = 0;
    uint32_t lastOffsetTime = 0;
public:
    AlkobusMenu(LiquidCrystal_I2C *lcd);
    void addProgram(Program * program);
    void selectorDown();
    void selectorUp();
    void setSelector(size_t selector);
    void loop();
    Program * getCurrentProgram();
    void redrawScreen();
    void printProgram(size_t position, Program *p, size_t offset);
    ~AlkobusMenu();
};


#endif //MEGA_POWER_DRIVER_ALKOBUSMENU_H
