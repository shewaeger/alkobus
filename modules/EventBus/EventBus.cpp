//
// Created by shewa on 19.10.19.
//

#include <list_utils.h>
#include <string.h>
#include "EventBus.h"

void EventBus::generateEvent(uint8_t type, void *data, size_t data_size) {
    Event event;
    event.type = type;
    event.data = malloc(data_size);
    memcpy(event.data, data, data_size);
    push_list_element(&(this->eventList), &event, sizeof(Event));
}

Event *EventBus::getLastEvent() {
    return (Event*)get_last_element(this->eventList);
}

void EventBus::removeEvent(Event *event) {
    free(event->data);
    remove_list_element_by_data(&this->eventList, event);
}


