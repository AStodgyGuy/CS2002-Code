#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/* Interface for integer MQueue */
typedef struct node{
	char data;
	struct node *next;
} Node;

/* The multi-threaded version contain a mutex 'access */
typedef struct {
	Node *head;
	Node *tail;
	pthread_mutex_t *access;
} MQueue;

void send_msg( MQueue *s, char value ); // enqueue
Node *read_msg( MQueue *s );            // dequeue
void initMQueue(MQueue *);
void printMQueue(MQueue *);
void clearMqueue(MQueue *);

#endif //MSG_QUEUE_H
