//
// Created by shewa on 19.10.19.
//

#ifndef MEGA_POWER_DRIVER_EVENTBUS_H
#define MEGA_POWER_DRIVER_EVENTBUS_H

#define LONG_PUSH_KEY_EVENT 1
#define SHORT_PUSH_KEY_EVENT 2
#define TEMPERATURE_UPDATE_EVENT 4

#include <stdlib.h>
#include <inttypes.h>
struct Event{
    void * data;
    uint8_t type;
};

struct list_element;

class EventBus {
private:
    list_element * eventList = NULL;
    list_element * observers = NULL;
public:
    void generateEvent(uint8_t type, void *data, size_t data_size);
    Event * getLastEvent();
    void removeEvent(Event * event);
};


#endif //MEGA_POWER_DRIVER_EVENTBUS_H
