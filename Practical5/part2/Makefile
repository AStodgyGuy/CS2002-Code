CC = clang
CFLAGS = -Wall -Wextra -g3 -pthread

all: main test_print_empty_queue test_print_queue test_print_queue_multithread

main: mq_test.h msg_queue.h 
	${CC} ${CFLAGS} msg_queue.c mq_test.c -o mq_test

test_print_queue: msg_queue.h
	${CC} ${CFLAGS} test_print_queue.c msg_queue.c -o test_print_queue

test_print_empty_queue: msg_queue.h
	${CC} ${CFLAGS} test_print_empty_queue.c msg_queue.c -o test_print_empty_queue

test_print_queue_multithread: msg_queue.h
	${CC} ${CFLAGS} test_print_multithread.c msg_queue.c -o test_print_queue_multithread

clean:
	rm mq_test test_print_queue test_print_empty_queue test_print_queue_multithread