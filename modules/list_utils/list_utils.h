#ifndef MEGA_POWER_DRIVER_TEMPERATURE_UTILS
#define MEGA_POWER_DRIVER_TEMPERATURE_UTILS

#include <stdlib.h>
struct list_element {
    list_element *prev;
    list_element *next;
    void *data;
};



#define CREATE_ELEMENT() ((list_element*)malloc(sizeof(list_element)))
#define DELETE_ELEMENT(el) (free(el))


void push_list_element(list_element *begin, void *data);
void *remove_list_element(list_element *begin, size_t pos);
void *get_last_element(list_element *begin);
void *get_list_element(list_element *begin, size_t pos);
size_t count_list(list_element *begin);
void *remove_list_element_by_data(list_element *begin, void * data);


#endif