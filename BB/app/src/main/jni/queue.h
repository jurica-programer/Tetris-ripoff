#ifndef QUEUE_H_
#define QUEUE_H_

#include "global_functions.h"
#include "common_functions.h"
#include <stdbool.h>
#include <string.h>

typedef enum data_type_e
{
    no_type = 0,
    integer_t,
    float_t,
    double_t,
    char_t,
    short_t,
    bool_t
}data_type;

struct node
{
    int* data;
    int (*print_state_ptr)(int);
    struct node* next;
};

struct _list
{
    struct node* head;
}list;


void enqueue(void* function, int data, data_type type);


int dequeue(void);

#endif

