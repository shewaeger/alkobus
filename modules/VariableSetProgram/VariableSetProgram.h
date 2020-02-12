//
// Created by shewa on 10.02.2020.
//

#ifndef MEGA_POWER_DRIVER_VARIABLESETPROGRAM_H
#define MEGA_POWER_DRIVER_VARIABLESETPROGRAM_H

#include <Program.h>
#include <LcdOverflowString.h>
#include <Keyboard.h>
#include <EventBus.h>
#include <LiquidCrystal_I2C.h>
template <typename T>
class VariableSetProgram : public Program {
protected:
    char * name;
    T * variable;
    T minValue;
    T maxValue;
    T step;
    bool isExit;
    T div;
    LcdOverflowString *lcdOverflowString;
public:
    VariableSetProgram(char *name, T *variable, T minValue, T maxValue, T step, T div = 1) {
        this->name = name;
        this->name = name;
        this->variable = variable;
        this->minValue = minValue;
        this->maxValue = maxValue;
        if(*this->variable > maxValue){
            *this->variable = minValue;
        }
        if(*this->variable < minValue){
            *this->variable = minValue;
        }
        this->step = step;
        this->div = div;
        this->isExit = false;
    }

    virtual void setMinValue(T minValue){
        this->minValue = minValue;
        if(*variable < minValue){
            *variable = minValue;
        }
    }

    virtual void setMaxValue(T maxValue){
        this->maxValue = maxValue;
        if(*variable > maxValue){
            *variable = maxValue;
        }
    }

    virtual void setup(){
        LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
        lcd->clear();
        lcdOverflowString = new LcdOverflowString(name, lcd, 800, 0);
        lcd->setCursor(0, 1);
        lcd->print(*variable / div);
        this->isExit = false;
    }

    virtual void loop(){
        if(isExit){
            delete lcdOverflowString;
            exit();
        }
        LiquidCrystal_I2C *lcd = ModManager::getManager()->getLCD();
        lcdOverflowString->loop();
        lcd->setCursor(0,1);
        lcd->print(*variable);
        lcd->print("                ");
    }

    virtual void event(Event *event){
        switch (event->type){
            case SHORT_PUSH_KEY_EVENT:
            case LONG_PUSH_KEY_EVENT:
                switch (*(uint8_t*)event->data){
                    case BUTTON_DOWN:
                        variableDown();
                        break;
                    case BUTTON_UP:
                        variableUp();
                        break;
                    case BUTTON_OK:
                        this->isExit = true;
                }
        }
    }

    virtual char *getName(){
        return name;
    }

    void variableUp(){
        *variable += step;
        if(*variable >= maxValue){
            *variable = maxValue;
        }
        if(*variable <= minValue){
            *variable = maxValue;
        }
    }
    void variableDown(){
        *variable -= step;
        if(*variable <= minValue){
            *variable = minValue;
        }
        if(*variable >= maxValue){
            *variable = minValue;
        }
    }
};

#endif //MEGA_POWER_DRIVER_VARIABLESETPROGRAM_H
