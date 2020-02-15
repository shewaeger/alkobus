#include <string.h>
#include <HardwareSerial.h>
#include "list_utils.h"

void push_list_element(list_element **begin, void *data, size_t size) {
    if (begin == NULL)
        return;
    list_element *element = CREATE_ELEMENT();
    element->data = malloc(size);
    memcpy(element->data, data, size);

    if(*begin == NULL){
        element->next = NULL;
        element->prev = NULL;
        *begin = element;
        return;
    }
    list_element *end;
    for (end = *begin; end->next != NULL; end = end->next);

    element->prev = end;
    element->next = NULL;
    end->next = element;
}

void remove_list_element(list_element **begin, size_t pos){
    if(begin == NULL || *begin == NULL)
        return;

    size_t i = 0;
    list_element* el;
    for(el = *begin; el->next != NULL && i < pos; el = el->next, i++);

    if(i != pos)
        return;

    free(el->data);

    list_element *next = el->next;
    list_element *prev = el->prev;

    if(next != NULL)
        next->prev = prev;
    if(prev != NULL)
        prev->next = next;


    if(el == *begin){
        if(el->next == NULL)
            *begin = NULL;
        else
            *begin = el->next;
    }

    free(el);
}

void remove_list_element_by_data(list_element **begin, void *data) {
    if(*begin == NULL)
        return;
    list_element *el;
    int i = 0;

    for (el = *begin; el != NULL && el->data != data; el = el->next, i++);

    if (el == NULL)
        return;

    remove_list_element(begin, i);
}

void *get_last_element(list_element *begin) {
    if (begin == NULL)
        return NULL;
    list_element *el;
    for (el = begin; el->next != NULL; el = el->next);
    return el->data;
}

void *get_list_element(list_element *begin, size_t pos) {
    if (begin == NULL)
        return NULL;
    size_t i = 0;
    list_element *element;
    for (element = begin; element->next != NULL && i != pos; element = element->next, i++);

    if (i != pos)
        return NULL;

    return element->data;
}

size_t count_list(list_element *begin) {
    size_t i = 0;
    list_element *el;
    for (el = begin; el != NULL; el = el->next, i++);
//    Serial.println("test");
    return i;
}