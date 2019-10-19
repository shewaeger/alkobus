//
// Created by shewa on 19.10.19.
//

#include <list_utils.h>
#include <string.h>
#include "EventBus.h"

void EventBus::generateEvent(uint8_t type, void *data, size_t data_size) {
    Event *event = (Event *)malloc(sizeof(Event));
    event->type = type;
    event->data = malloc(data_size);
    memcpy(event->data, data, data_size);
    if(this->eventList == NULL){
        this->eventList = CREATE_ELEMENT();
        this->eventList->next = NULL;
        this->eventList->prev = NULL;
        this->eventList->data = event;
    } else{
        push_list_element(this->eventList, event);
    }
}

Event *EventBus::getLastEvent() {
    return (Event*)get_last_element(this->eventList);
}

void EventBus::removeEvent(Event *event) {
    if(event != remove_list_element_by_data(this->eventList, event))
        return;
    free(event->data);
    free(event);
}


