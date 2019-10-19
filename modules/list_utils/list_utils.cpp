#include "list_utils.h"

void push_list_element(list_element *begin, void *data) {
    if(begin == NULL)
        return;
    list_element *element = CREATE_ELEMENT();
    list_element *end;
    for (end = begin; end->next != NULL; end = end->next);

    element->data = data;
    element->prev = end;
    element->next = NULL;
    end->next = element;
}

void *remove_list_element(list_element *begin, size_t pos) {
    void *data;
    size_t i = 0;
    list_element *element;
    list_element *prev;
    list_element *next;
    for (element = begin; element->next != NULL && i < pos; element = element->next, i++);

    if (i != pos)
        return NULL;

    data = element->data;

    prev = element->prev;
    next = element->next;
    DELETE_ELEMENT(element);

    prev->next = next;
    next->prev = prev;

    return data;
}

void *remove_list_element_by_data(list_element *begin, void * data){
    list_element * el;
    int i = 0;

    for(el = begin; el != NULL && el->data != data; el = el->next, i++);

    if(el == NULL)
        return NULL;

    return remove_list_element(begin, i);
}

void *get_last_element(list_element *begin){
    if(begin == NULL)
        return NULL;
    list_element *el;
    for(el = begin; el->next != NULL; el = el->next);
    return el->data;
}

void *get_list_element(list_element *begin, size_t pos) {
    if(begin == NULL)
        return NULL;
    size_t i = 0;
    list_element *element;
    for (element = begin;  element->next != NULL && i < pos; element = element->next, i++);

    if (i != pos)
        return NULL;

    return element->data;
}

size_t count_list(list_element *begin) {
    size_t i = 0;
    list_element *el;
    for (el = begin; el != NULL;  el = el->next, i++);
    return i;
}