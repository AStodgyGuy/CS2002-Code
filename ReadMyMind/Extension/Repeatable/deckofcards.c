#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "deck.h"

// Enqueue
void enqueue(Card* c, Deck* deck) {
    if (deck->front == NULL) {
        deck->front = deck->rear = c;
        deck->size++;
        return;
    }
    deck->rear->next = c;
    deck->rear = c;
    deck->rear->next = NULL;
    deck->size++;
}

//dequeue
Card* dequeue(Deck* deck) {
    Card* temp = deck->front;
    if (deck->front == NULL) {
        return NULL;
    }

    if (deck->front == deck->rear) {
        deck->front = deck->rear = NULL;
    } else {
        deck->front = deck->front->next;
    }
    deck->size--;
    return temp;
}

//print out ranks
void printRank(int rank) {
    switch (rank) {
        case 12:
            printf("K");
            break;
        case 11: 
            printf("Q");
            break;
        case 10:
            printf("J");
            break;
        case 9:
            printf("10");
            break;
        case 0:
            printf("A");
            break;
        default:
            printf("%d", rank + 1);
            break;
    }
}

//print out suit
void printSuit(int suit) {
    switch (suit) {
        case 0:
            printf("C");
            break;
        case 1:
            printf("S");
            break;
        case 2:
            printf("H");
            break;
        default:
            printf("D");
            break;
    }
}

//print card
void printCard(Card* c) {
    printRank(c->rank);
    printSuit(c->suit);
}

int getSize(Deck* deck) {
    return deck->size;
}

//contains method
int queueContains(Card* c, Deck* deck) {
    Card* current_card = deck->front;
    int size = getSize(deck);
    if (size == 0) {
        return false;
    }
    while (size > 0) {
        if (c->rank == current_card->rank && c->suit == current_card->suit) {
            return true;
        }
        current_card = current_card->next;
        size--;
    }
    return false;
}

//empty method
void empty(Deck* deck) {
    int deckSize = getSize(deck);
    if (deckSize == 0) {
        return;
    }

    while (deckSize > 0) {
        free(dequeue(deck));
        deckSize--;
    }
}

//get the nth card in the queue
Card* getCard(Deck* deck, int no_of_iterations) {
    Card* temp = deck->front;
    int iteration = 0;
    while (iteration < no_of_iterations) {
        if (temp->next == NULL) {
            break;
        }
        temp = temp->next;
        iteration++;

    }

    return temp;
}
