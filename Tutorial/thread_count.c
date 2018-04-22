/*
Thread interleaving demo for CS2002 tutorial

Saleem Bhatti, 08 April 2012
MacOSX 10.6 and 10.7
Marwan Fayed, April 2018 (modifications)

compile: 
  clang -o thread_count thread_count.c -pthread

run:
  ./thread_count

or:
  ./therad_count join

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int G_threads_max = 20;

int G_counter = 0;

void *incr(void *arg) {
	/* Modern CPUs too fast/parallel; force 50us sleep. */
	nanosleep((const struct timespec[]){{0, 50000L}}, NULL);
	G_counter += 1;
	printf("%02i incr() G_counter: %i\n", *((int *) arg), G_counter);
	return (void *) 0;
}

void *decr(void *arg) {
	/* Modern CPUs too fast/parallel; force 50us sleep. */
	nanosleep((const struct timespec[]){{0, 50000L}}, NULL);
	G_counter -= 1;
	printf("%02i decr() G_counter: %i\n", *((int *) arg), G_counter);
	return (void *) 0;
}


int main(int argc, char* argv[]){

	pthread_t pt[G_threads_max];
	int c, i, do_join;

	if (argc == 2 && strcmp(argv[1], "join") == 0)
		do_join = 1;
	else do_join = 0;

	printf("-- start of main() G_counter: %i\n", G_counter);
	for (c = 0; c < G_threads_max; c += 2) {

		i = c; printf("main() i: %02i\n", i);
		pthread_create(&pt[i], NULL, incr, (void *) &i);

		i += 1; printf("main() i: %02i\n", i);
		pthread_create(&pt[i], NULL, decr, (void *) &i);
	}

  if (do_join) {
  	printf("-- before join in main() G_counter: %i\n", G_counter);

		for (c = 0; c < G_threads_max; c += 1) {
			pthread_join(pt[c], (void **) 0);
			printf("main() pthread_join(%02i)\n", c);
		}
		printf("\n");
	}

	printf("-- end of main() G_counter: %i\n", G_counter);

	return 0;
}
