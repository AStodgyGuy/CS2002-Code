CC = clang
CFLAGS = -Wall -Wextra

all: main

main: card.h deck.h deckofcards.c readmymind.c
	${CC} ${CFLAGS} deckofcards.c readmymind.c -o readmymind

clean: 
	rm -rf readmymind