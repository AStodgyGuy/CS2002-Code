CC = clang
CFLAGS = -Wall -Wextra

all: main

main: card.h deck.h deckofcards.c favouritenumber.c
	${CC} ${CFLAGS} deckofcards.c favouritenumber.c -o favouritenumber

test: card.h deck.h deckofcards.c test.c
	${CC} ${CFLAGS} deckofcards.c test.c -o test

clean: 
	rm -rf favouritenumber