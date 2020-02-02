//
// Created by shewa on 31.12.19.
//

#ifndef MEGA_POWER_DRIVER_VALVE_H
#define MEGA_POWER_DRIVER_VALVE_H

#include <stdarg.h>
#include <list_utils.h>

class Valve {
    int pin;
    bool mode;
    uint64_t pwmCount;
    bool pwmStatus;
    uint64_t pwm;
    uint64_t openingDuration;
    bool pwmScale;
    uint64_t lastPWM;
    uint64_t lastDuration;
public:
    /***
     * Constructor
     * @param pin - digital pin that connects to valve
     * @param mode - mode: false - normal-open, true - normal-closed
     */
    Valve(int pin, bool mode = false);

    void open();

    void close();

    /**
     * Set pwm of valve.
     * @param pwm count per pwmScale
     * @param pwmScale false - per minute, true - per hour
     */
    void setPWM(uint64_t pwmCount, bool pwmScale = false);

    /**
     * Set opening duration
     * @param duration - duration in ms
     */
    void setOpeningDuration(uint64_t duration);

    void loop();

    uint64_t getPWMCount();
    uint64_t getPWMScale();
    uint64_t getOpeningDuration();
    void setPWMStatus(bool status);
    bool switchPWMStatus();
    ~Valve();
};


#endif //MEGA_POWER_DRIVER_VALVE_H
