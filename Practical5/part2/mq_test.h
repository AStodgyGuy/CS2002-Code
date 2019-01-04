#ifndef MSG_TEST_H
#define MSG_TEST_H

#include "msg_queue.h"
#include <pthread.h>
#include <unistd.h>
#include<assert.h>
#include <stdio.h>
#include <stdlib.h>

struct thread_args {
    MQueue* queue;
    int value;
};

//general methods for tests
int sumcheck(MQueue* s);
void* add_queue(void* argp);
void* remove_queue(void* argp);

//basic queue tests
void test_queue_init(MQueue* s);
void test_enqueue(MQueue* s);
void test_five_enqueue(MQueue* s);
void test_dequeue(MQueue* s);
void test_dequeue_five(MQueue* s);
void test_invalid_dequeue(MQueue* s);
void test_print_queue();
void test_print_empty_queue();
void test_clear_queue(MQueue* s);
void test_clear_empty_queue(MQueue* s);

//multithreading tests
void test_five_enqueue_mt(MQueue* s);
void test_dequeue_five_mt(MQueue* s);
void test_enqueue_and_dequeue_five_mt(MQueue* s);
void test_print_queue_mt();


#endif
