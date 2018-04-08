CC = gcc -std=c99
FLAGS = -Wall -Wextra -g3

circuits: main.c circuit.h circuit.c
	${CC} ${FLAGS} main.c circuit.c -o circuits

clean:
	rm -rf circuits
