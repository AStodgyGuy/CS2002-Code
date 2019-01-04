CC = gcc -std=c99
FLAGS = -Wall -Wextra

all: clean circuits

circuits: main.c circuit.h circuit.c
	${CC} ${FLAGS} main.c circuit.c -o circuits

clean:
	rm -rf circuits
