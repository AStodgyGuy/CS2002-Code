#ifndef PRINT_MULTI
#define PRINT_MULTI

#include "msg_queue.h"

struct thread_args {
    MQueue* queue;
    int value;
};

#endif