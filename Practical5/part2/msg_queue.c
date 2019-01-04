#include "msg_queue.h"

/**
 * Method which sends a message into the queue
 */
Node* read_msg(MQueue* s)
{
    //lock the queue
    pthread_mutex_lock(s->access);

    //get the element to be returned
    Node* msg = s->head;

    //if the queue is empty, return null
    if (s->head == NULL) {
        pthread_mutex_unlock(s->access);
        return NULL;
    }

    //check whether there is only one element in the queue, if so, dequeue operation will affect both head and tail
    if (s->head == s->tail) {
        s->head = s->tail = NULL;
    //otherwise, set the head to the current head's next element
    } else {
        s->head = s->head->next;
    }

    //unlock the queue
    pthread_mutex_unlock(s->access);

    return msg;
}


/**
 * Method which reads a message from the queue
 */
void send_msg(MQueue* s, int value)
{
    //lock queue
    pthread_mutex_lock(s->access);

    //malloc new element to be added into the queue
    Node* n = malloc(sizeof(Node));
    assert(n != NULL);
    n->data = value;

    //if head is null, tail is also null
    if (s->head == NULL) 
    {
        //set head and tail data fields to new value
        s->head = n;
        s->tail = n;
        pthread_mutex_unlock(s->access);
        return;
    }
    //if head is not null, tail exists separetly from head
    else
    {
        //set the current tail's next element to the new element
        s->tail->next = n;
        //set the current tail to the new element
        s->tail = n;
        //set the next element of the new element to null
        s->tail->next = NULL;
    }

    //unlock the queue
    pthread_mutex_unlock(s->access);
}

/**
 * Method which initializes a queue
 */
void initMQueue(MQueue* s)
{
    //set head and tail of queue to null
    s->head = NULL;
    s->tail = NULL;
    //set mutex
    pthread_mutex_t* mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    int err = pthread_mutex_init(mutex, NULL);
    assert(err == 0);
    s->access = mutex;
}

/**
 * Method which prints the queue
 */
void printMQueue(MQueue* s)
{
    //lock queue
    pthread_mutex_lock(s->access);

    //set variable to head of queue
    Node* msg = s->head;

    //iterate through each element in the queue
    while (msg != NULL)
    {
        //print out the data at each node
        fprintf(stdout, "%d", msg->data);
        //move on to next node
        msg = msg->next;
    }

    //unlock queue
    pthread_mutex_unlock(s->access);
}

/**
 * Method which clears the MQueue
 */
void clearMQueue(MQueue* s)
{    
    //lock queue
    // pthread_mutex_lock(s->access);

    //queue is empty there is nothing to free
    if (s->head == NULL)
    {
        //unlock queue
        pthread_mutex_unlock(s->access);
        return;
    }

    //free all elements in the queue
    while(s->head != NULL)
    {
        free(read_msg(s));
    }

    //unlock queue
    // pthread_mutex_unlock(s->access);
}
