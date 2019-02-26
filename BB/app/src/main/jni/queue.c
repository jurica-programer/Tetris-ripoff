#include "queue.h"

/****************************************
 * enqueue function
 ****************************************/
void enqueue(void* function, int data, data_type type)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    memset(new_node, 0x00, sizeof(struct node));
    if( type == integer_t )
    {
        int* value = (int*) malloc(sizeof(int));
        *value = data;
        new_node->data = value;
    }
    //TODO popravi warning
    new_node->print_state_ptr = (int(*)(void*))function;
    struct node* temp_node = NULL;
    if( !list.head )
    {
        list.head = new_node;
    }
    else
    {
        temp_node = list.head;
        while( temp_node->next )
        {
            temp_node = temp_node->next;
        }
        temp_node->next = new_node;
    }
    //sem_post(&GameContext.reading_semaphore);
}

/****************************************
 * dequeue function
 ****************************************/
int dequeue(void)
{
    if (list.head) {
        //sem_wait(&GameContext.reading_semaphore);

        int data = 0;
        struct node* temp_node = list.head->next;
        if (list.head->data)
        {
            data = *list.head->data;
        }
        //C:\Users\Jura\AndroidStudioProjects\BB\app\src\main\jni\queue.c:17:31: warning: assignment from incompatible pointer type ovo:print_state_ptr
        list.head->print_state_ptr(data);
        if(list.head->data)
        {
            //todo PROVJER duplo malloc i free
            free(list.head->data);
        }
        if(list.head)
        {
            free(list.head);
        }
        list.head = temp_node;
        return 1;
    }
    else
    {
        return 0;
    }
}