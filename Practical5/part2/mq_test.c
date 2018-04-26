#include "mq_test.h"
#include <sys/wait.h>
#include <string.h>

int main()
{
    MQueue* s = malloc(sizeof(MQueue));
    if (s == NULL)
    {
        perror("Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    //basic queue tests

    //test initialisation
    printf("Testing... test_queue_init()\n");
    test_queue_init(s);
    printf("Test pass\n");

    //test clear queue
    printf("Testing... test_clear_queue()\n");
    test_clear_queue(s);
    printf("Test pass\n");

    //test clear empty queue
    printf("Testing... test_clear_empty_queue()\n");
    test_clear_empty_queue(s);
    printf("Test pass\n");

    //test print queue
    printf("Testing.. test_print_queue()\n");
    test_print_queue();
    printf("Test pass\n");

    //test print empty queue
    printf("Testing.. test_print_empty_queue()\n");
    test_print_empty_queue();
    printf("Test pass\n");

    //test enqueue
    printf("Testing... test_enqueue()\n");
    test_enqueue(s);
    clearMQueue(s); // clear queue before next test
    printf("Test pass\n");

    //test enqueuing 5 elements
    printf("Testing... test_five_enqueue()\n");
    test_five_enqueue(s);
    clearMQueue(s);
    printf("Test pass\n");

    //test dequeing an element
    printf("Testing... test_dequeue()\n");
    test_dequeue(s);
    clearMQueue(s);
    printf("Test pass\n");

    //test dequeing five elements
    printf("Testing... test_dequeue_five()\n");
    test_dequeue_five(s);
    clearMQueue(s);
    printf("Test pass\n");

    //test dequeing when there is no elements
    printf("Testing... test_invalid_dequeue()\n");
    test_invalid_dequeue(s);
    clearMQueue(s);
    printf("Test pass\n");

    //multithreading tests

    //test enqueing five elements using multiple threads
    printf("Testing... test_five_enqueue_mt()\n");
    test_five_enqueue_mt(s);
    clearMQueue(s);
    printf("Test pass\n");

    //test enqueing five elements using multiple threads
    printf("Testing... test_dequeue_five_mt()\n");
    test_dequeue_five_mt(s);
    clearMQueue(s);
    printf("Test pass\n");

    //test enqueing and deqeuing elements using multiple threads
    printf("Testing... test_enqueue_and_dequeue_five_mt()\n");
    test_enqueue_and_dequeue_five_mt(s);
    clearMQueue(s);
    printf("Test pass\n");

    //test print using threads
    printf("Testing... test_print_queue_mt()\n");
    test_print_queue_mt();
    printf("Test pass\n");

    free(s->head);
    free(s->tail);
    free(s->access);
    free(s);
    return 0;
}

/**
 * Test which tests the initilisation of the queue
 */
void test_queue_init(MQueue* s) 
{
    initMQueue(s);
    assert(s->head == NULL);
    assert(s->tail == NULL);
}

/**
 * Test which tests the enqueue method of the queue
 */
void test_enqueue(MQueue* s)
{
    send_msg(s, 2);
    assert(s->head->data == 2);
    assert(s->tail->data == 2);
}

/**
 * Test which tests enqueing multiple elements onto the queue
 */
void test_five_enqueue(MQueue* s)
{
    send_msg(s, 1);
    send_msg(s, 2);
    send_msg(s, 3);
    send_msg(s, 4);
    send_msg(s, 5);
    assert(s->head->data == 1);
    assert(s->head->next->data == 2);
    assert(s->head->next->next->data == 3);
    assert(s->head->next->next->next->data == 4);
    assert(s->tail == s->head->next->next->next->next);
    assert(s->head->next->next->next->next->data == 5);
    assert(s->tail->data == 5);
}

/**
 * Test dequeing the queue
 */
void test_dequeue(MQueue* s)
{
    send_msg(s, 1);
    assert(s->head->data == s->tail->data == 1);
    Node* object = read_msg(s);
    assert(object->data == 1);
    free(object);
}

/**
 * Test dequeing 5 elements
 */
void test_dequeue_five(MQueue* s)
{
    send_msg(s, 1);
    send_msg(s, 2);
    send_msg(s, 3);
    send_msg(s, 4);
    send_msg(s, 5);
    Node* object1 = read_msg(s);
    Node* object2 = read_msg(s);
    Node* object3 = read_msg(s);
    Node* object4 = read_msg(s);
    Node* object5 = read_msg(s);
    assert(object1->data == 1);
    assert(object2->data == 2);
    assert(object3->data == 3);    
    assert(object4->data == 4);
    assert(object5->data == 5);
    free(object1);
    free(object2);
    free(object3);
    free(object4);
    free(object5);
}

/**
 * Test invalid dequeue
 */
void test_invalid_dequeue(MQueue* s)
{
    assert(read_msg(s) == NULL);
}

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

/**
 * Entry function 'remove' for the multithreaded process
 */
void* remove_queue(void* argp)
{
    struct thread_args *args = argp;
    Node* element = read_msg(args->queue);
    free(args);
    return (void*) element;
}

/**
 * Sum check for the elements inside the queue
 */
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

/**
 * Test 5 threads adding to the queue
 */
void test_five_enqueue_mt(MQueue* s)
{
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

    assert(sumcheck(s) == 10+20+30+40+50);
}


/**
 * Test multi-thread dequeue
 */
void test_dequeue_five_mt(MQueue* s)
{
    int nthreads = 5;
    pthread_t threads[nthreads];

    void *val1, *val2, *val3, *val4, *val5;

    //single thread enqueue
    send_msg(s, 10);
    send_msg(s, 20);
    send_msg(s, 30);
    send_msg(s, 40);
    send_msg(s, 50);

    struct thread_args* arg1 = malloc(sizeof(*arg1));
    assert(arg1 != NULL);
    arg1->queue = s;
    assert((pthread_create(&threads[0], NULL, remove_queue, arg1)) == 0);

    struct thread_args* arg2 = malloc(sizeof(*arg2));
    assert(arg2 != NULL);
    arg2->queue = s;
    assert((pthread_create(&threads[1], NULL, remove_queue, arg2)) == 0);

    struct thread_args* arg3 = malloc(sizeof(*arg3));
    assert(arg3 != NULL);
    arg3->queue = s;
    assert((pthread_create(&threads[2], NULL, remove_queue, arg3)) == 0);

    struct thread_args* arg4 = malloc(sizeof(*arg4));
    assert(arg4 != NULL);
    arg4->queue = s;
    assert((pthread_create(&threads[3], NULL, remove_queue, arg4)) == 0);

    struct thread_args* arg5 = malloc(sizeof(*arg5));
    assert(arg5 != NULL);
    arg5->queue = s;
    assert((pthread_create(&threads[4], NULL, remove_queue, arg5)) == 0);

    assert((pthread_join(threads[0], &val1)) == 0);
    assert((pthread_join(threads[1], &val2)) == 0);
    assert((pthread_join(threads[2], &val3)) == 0);
    assert((pthread_join(threads[3], &val4)) == 0);
    assert((pthread_join(threads[4], &val5)) == 0);

    assert(((Node*)val1)->data + ((Node*)val2)->data + ((Node*)val3)->data + ((Node*)val4)->data + ((Node*)val5)->data == 10+20+30+40+50);

}

/**
 * Test multi-thread dequeue and enqueue
 */
void test_enqueue_and_dequeue_five_mt(MQueue* s)
{
    int nthreads = 10;
    pthread_t threads[nthreads];

    void *val1, *val2, *val3, *val4, *val5;

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

    struct thread_args* arg6 = malloc(sizeof(*arg6));
    assert(arg6 != NULL);
    arg6->queue = s;
    assert((pthread_create(&threads[5], NULL, remove_queue, arg6)) == 0);

    struct thread_args* arg7 = malloc(sizeof(*arg7));
    assert(arg7 != NULL);
    arg7->queue = s;
    assert((pthread_create(&threads[6], NULL, remove_queue, arg7)) == 0);

    struct thread_args* arg8 = malloc(sizeof(*arg8));
    assert(arg8 != NULL);
    arg8->queue = s;
    assert((pthread_create(&threads[7], NULL, remove_queue, arg8)) == 0);

    struct thread_args* arg9 = malloc(sizeof(*arg9));
    assert(arg9 != NULL);
    arg9->queue = s;
    assert((pthread_create(&threads[8], NULL, remove_queue, arg9)) == 0);

    struct thread_args* arg10 = malloc(sizeof(*arg10));
    assert(arg10 != NULL);
    arg10->queue = s;
    assert((pthread_create(&threads[9], NULL, remove_queue, arg10)) == 0);

    assert((pthread_join(threads[5], &val1)) == 0);
    assert((pthread_join(threads[6], &val2)) == 0);
    assert((pthread_join(threads[7], &val3)) == 0);
    assert((pthread_join(threads[8], &val4)) == 0);
    assert((pthread_join(threads[9], &val5)) == 0);

    assert(((Node*)val1)->data + ((Node*)val2)->data + ((Node*)val3)->data + ((Node*)val4)->data + ((Node*)val5)->data == 10+20+30+40+50);
}

/**
 * Tests the print queue method
 */
void test_print_queue()
{
    int fd[2];
    pipe(fd);
    char enc = EOF;
    char res[5];

    //run the print method elsewhere and pipe output back to parent
    int child = fork();
    if(child == 0){ 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        system("./test_print_queue");
        exit(0);
    }else{
        close(fd[1]);
        int i = 0;
        //read output given by the print method
        while (read(fd[0], &enc, sizeof(char)) > 0)
        {
            res[i] = enc;
            ++i;
        }
        assert(res[0] == '1');
        assert(res[1] == '2');
        assert(res[2] == '3');
        assert(res[3] == '4');
        assert(res[4] == '5');
        wait(NULL);
    }
}

/**
 * Tests printing an empty queue
 */
void test_print_empty_queue()
{
    int fd[2];
    pipe(fd);
    char enc = EOF;

    int child = fork();
    if(child == 0){ 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        system("./test_print_empty_queue");
        exit(0);
    }else{
        close(fd[1]);
        assert(read(fd[0], &enc, sizeof(char)) == 0);
        wait(NULL);
    }
}

/**
 * Tests the clear queue method
 */
void test_clear_queue(MQueue* s)
{
    send_msg(s, 1);
    send_msg(s, 2);
    send_msg(s, 3);
    send_msg(s, 4);
    send_msg(s, 5);

    clearMQueue(s);

    assert(s->head == NULL);
    assert(s->tail == NULL);
}

/**
 * Tests the clear empty queue on an empty queue
 */
void test_clear_empty_queue(MQueue* s)
{
    clearMQueue(s);

    assert(s->head == NULL);
    assert(s->tail == NULL);
}

/**
 * Tests that print the queue using multiple threads
 */
void test_print_queue_mt()
{
    int fd[2];
    pipe(fd);
    char enc = EOF;
    char res[10];

    int child = fork();
    if(child == 0){ 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        system("./test_print_queue_multithread");
        exit(0);
    }else{
        close(fd[1]);
        int i = 0;
        while (read(fd[0], &enc, sizeof(char)) > 0)
        {
            if (i % 2 == 0)
            {
                res[i] = enc;
            }
            ++i;
            
        }
        //convert received chars to integers
        int r1 = atoi(&res[0]);
        int r2 = atoi(&res[1]);
        int r3 = atoi(&res[2]);
        int r4 = atoi(&res[3]);
        int r5 = atoi(&res[4]);
        int r6 = atoi(&res[5]);
        int r7 = atoi(&res[6]);
        int r8 = atoi(&res[7]);
        int r9 = atoi(&res[8]);
        int r10 = atoi(&res[9]);
        
        assert(r1+r2+r3+r4+r5+r6+r7+r8+r9+r10 == 1+0+2+0+3+0+4+0+5+0);
        wait(NULL);
    }
}
