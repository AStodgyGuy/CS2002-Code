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

//contains method
int queueContains(Card* c, Deck* deck) {
    Card* current_card = deck->front;
    int size = deck->size;
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
    int deckSize = deck->size;
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
