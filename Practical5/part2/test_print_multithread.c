#include "test_print_multithread.h"
#include <sys/wait.h>

/**
 * Entry function 'add' for the multithread process
 */
void* add_queue(void* argp)
{
    struct thread_args *args = argp;
    send_msg(args->queue, args->value);
    free(args);
    return (void*) 0;
}

int sumcheck(MQueue* s)
{
    int count = 0;
    Node* temp = s->head;
    while (temp != NULL)
    {
        count += temp->data;
        temp = temp->next;
    }
    return count;
}


int main()
{
    MQueue* s = malloc(sizeof(MQueue));
    if (s == NULL)
    {
        perror("Error: malloc failed");
        exit(EXIT_FAILURE);
    }
    initMQueue(s);

    int nthreads = 5;
    pthread_t threads[nthreads];

    struct thread_args* arg1 = malloc(sizeof(*arg1));
    assert(arg1 != NULL);
    arg1->queue = s;
    arg1->value = 10;
    assert((pthread_create(&threads[0], NULL, add_queue, arg1)) == 0);

    struct thread_args* arg2 = malloc(sizeof(*arg2));
    assert(arg2 != NULL);
    arg2->queue = s;
    arg2->value = 20;
    assert((pthread_create(&threads[1], NULL, add_queue, arg2)) == 0);

    struct thread_args* arg3 = malloc(sizeof(*arg3));
    assert(arg3 != NULL);
    arg3->queue = s;
    arg3->value = 30;
    assert((pthread_create(&threads[2], NULL, add_queue, arg3)) == 0);

    struct thread_args* arg4 = malloc(sizeof(*arg4));
    assert(arg4 != NULL);
    arg4->queue = s;
    arg4->value = 40;
    assert((pthread_create(&threads[3], NULL, add_queue, arg4)) == 0);

    struct thread_args* arg5 = malloc(sizeof(*arg5));
    assert(arg5 != NULL);
    arg5->queue = s;
    arg5->value = 50;
    assert((pthread_create(&threads[4], NULL, add_queue, arg5)) == 0);

    assert((pthread_join(threads[0], NULL)) == 0);
    assert((pthread_join(threads[1], NULL)) == 0);
    assert((pthread_join(threads[2], NULL)) == 0);
    assert((pthread_join(threads[3], NULL)) == 0);
    assert((pthread_join(threads[4], NULL)) == 0);

    printMQueue(s);
    wait(NULL);

    return 0;
}