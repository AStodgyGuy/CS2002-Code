/*
Thread interleaving demo for CS2002 practical SP2 - with mutex

Saleem Bhatti, 08 April 2012
MacOSX 10.6 and 10.7
Marwan Fayed, April 2018 (modifications)

compile:
  clang -o thread_count_mutex thread_count_mutex.c

run:
  ./thread_count_mutex

or:
  ./thread_count_mutex join

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int G_threads_max = 20;

typedef struct Counter_s {
  pthread_mutex_t access;
  int counter;
} Counter_t;

Counter_t G_counter;

void *incr(void *arg) {
  /* Modern CPUs too fast/parallel; force 50us sleep. */
	nanosleep((const struct timespec[]){{0, 50000L}}, NULL);

	pthread_mutex_lock(&G_counter.access);
	  G_counter.counter += 1;
	  printf("%02i incr() G_counter: %i\n", *((int *) arg), G_counter.counter);
	pthread_mutex_unlock(&G_counter.access);
	return (void *) 0;
}

void *decr(void *arg) {
  /* Modern CPUs too fast/parallel; force 50us sleep. */
	nanosleep((const struct timespec[]){{0, 50000L}}, NULL);

	pthread_mutex_lock(&G_counter.access);
	  G_counter.counter -= 1;
	  printf("%02i decr() G_counter: %i\n", *((int *) arg), G_counter.counter);
	pthread_mutex_unlock(&G_counter.access);
	return (void *) 0;
}


int main(int argc, char* argv[]){

	pthread_t pt[G_threads_max];
	int c, i, do_join;

  G_counter.counter = 0;
  pthread_mutex_init(&G_counter.access, NULL);

	if (argc == 2 && strcmp(argv[1], "join") == 0)
		do_join = 1;
	else do_join = 0;

	printf("-- start of main() G_counter: %i\n", G_counter.counter);
	for (c = 0; c < G_threads_max; c += 2) {

		i = c; printf("main() i: %02i\n", i);
		pthread_create(&pt[i], NULL, incr, (void *) &i);

		i += 1; printf("main() i: %02i\n", i);
		pthread_create(&pt[i], NULL, decr, (void *) &i);
	}

  if (do_join) {
  	printf("-- before join in main() G_counter: %i\n", G_counter.counter);

		for (c = 0; c < G_threads_max; c += 1) {
			pthread_join(pt[c], (void **) 0);
			printf("main() pthread_join(%02i)\n", c);
		}
		printf("\n");
	}

	printf("-- end of main() G_counter: %i\n", G_counter.counter);

	return 0;
}
