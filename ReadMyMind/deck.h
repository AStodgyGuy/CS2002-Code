#include "card.h"

typedef struct Deck {
    Card* front;
    Card* rear;
    int size;
} Deck;

void enqueue(Card* c, Deck* deck);
Card* dequeue(Deck* deck);
int queueContains(Card* c, Deck* deck);
void empty(Deck* deck);
Card* getCard(Deck* deck, int no_of_iterations);
