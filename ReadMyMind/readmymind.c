#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "deck.h"

// method to create deck
Deck* createDeck(Deck* deck, int no_of_cards, int suits, int ranks) {
    srand(time(NULL));
    int i = 0;
    while (i < no_of_cards) {
        Card* card_pointer = malloc(sizeof(Card));
        card_pointer->rank = rand() % ranks;
        card_pointer->suit = rand() % suits;
        if (!queueContains(card_pointer, deck)) {
            enqueue(card_pointer, deck);
            i++;
        } else {
            free(card_pointer);
        }
    }

    return deck;
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
            printf("♣");
            break;
        case 1:
            printf("♠");
            break;
        case 2:
            printf("♥");
            break;
        default:
            printf("♦");
            break;
    }
}

//print card
void printCard(Card* c) {
    printRank(c->rank);
    printSuit(c->suit);
}

//method to print contents of deck
void printDeck(Deck* deck, int rows, int columns) {
    Card* temp = deck->front;
    printf("%d\t%d\t%d\n", 1, 2, 3);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printCard(temp);
            printf("\t");
            temp = temp->next;
        }
        printf("\n");
    }
}

//method to get user input and input validation
int getUserInput() {
    int user_input;
    char initial_input[100];
    printf("\nThink of a card displayed above, enter which column it is in or enter 0 to exit: ");
    while(1) {
        scanf("%s", initial_input);
        if (sscanf(initial_input,"%d", &user_input)) {
            if (user_input == 0 || user_input == 1 || user_input == 2 || user_input == 3) {
                break;
            }
        }
        printf("Invalid input! Enter which column it is in or 0 to exit: ");
    }
    return user_input;   
}

//method to rotate decks
Deck* combineDecks(Deck* deck, Deck* deck_to_middle, Deck* first_deck_to_rotate, Deck* second_deck_to_rotate) {
    int i = 0;
    int size_of_deck = first_deck_to_rotate->size;
    
    //dequeue all elements in column deck and enqueue it into the main deck
    while (i < size_of_deck) {
        enqueue(dequeue(first_deck_to_rotate), deck);
        i++;
    }

    i = 0;
    //dequeue all elements in column deck and enqueue it into the main deck
    while (i < size_of_deck) {
        enqueue(dequeue(deck_to_middle), deck);
        i++;
    }

    i = 0;
    //dequeue all elements in column deck and enqueue it into the main deck
    while (i < size_of_deck) {
        enqueue(dequeue(second_deck_to_rotate), deck);
        i++;
    }

    return deck;
}

//method to collect the cards
Deck* collectDeck(Deck* deck, int user_input) {

    //three decks
    Deck* deck_one = malloc(sizeof(Deck));
    deck_one->front = NULL;
    deck_one->rear = NULL;
    Deck* deck_two = malloc(sizeof(Deck));
    deck_two->front = NULL;
    deck_two->rear = NULL;
    Deck* deck_three = malloc(sizeof(Deck));
    deck_three->front = NULL;
    deck_three->rear = NULL;

    int no_of_cards = deck->size;

    //go through every card in deck
    for (int i = 0; i < no_of_cards; i++) {
        switch (i % 3) {
            //column 1 cards
            case 0:
                enqueue(dequeue(deck) ,deck_one);
                break;
            //column 2 cards
            case 1:
                enqueue(dequeue(deck) ,deck_two);
                break;
            //column 3 cards
            case 2:
                enqueue(dequeue(deck) ,deck_three);
                break;
        }
    }

    deck->front = NULL;
    deck->rear = NULL;

    //put user deck in the middle
    switch(user_input) {
        //column 1 goes to the middle
        case 1:
            deck = combineDecks(deck, deck_one, deck_two, deck_three);
            break;

        //column 2 goes to the middle
        case 2:
            deck = combineDecks(deck, deck_two, deck_one, deck_three);
            break;

        //column 3 goes to the middle
        case 3:
            deck = combineDecks(deck, deck_three, deck_two, deck_one);
            break;
    }

    //free the decks
    free(deck_one);
    free(deck_two);
    free(deck_three);

    //return the deck
    return deck;
}

//main method
int main() {

    int no_of_rows = 7;
    int no_of_columns = 3;
    int no_of_cards = no_of_columns * no_of_rows;
    int no_of_suits = 4;
    int no_of_ranks = 13;
    int no_of_repitions = 3;
    int prediction = no_of_cards / 2;

    //create deck of 21 random cards
    Deck* deck_pointer = malloc(sizeof(Deck));
    deck_pointer->front = NULL;
    deck_pointer->rear = NULL;
    deck_pointer->size = 0;
    deck_pointer = createDeck(deck_pointer, no_of_cards, no_of_suits, no_of_ranks);

    //display the cards
    printDeck(deck_pointer, no_of_rows, no_of_columns);
    int user_input;
    //the trick
    for (int i = 0; i < no_of_repitions; i++) {
        //get input
        user_input = getUserInput();
        if (user_input == 0) {
            //free everything
            printf("Exiting the program...\n");
            empty(deck_pointer);
            free(deck_pointer);
            return 0;
        }
        //collect deck
        deck_pointer = collectDeck(deck_pointer, user_input);
        //print deck
        printDeck(deck_pointer, no_of_rows, no_of_columns);
    }

    //make prediction
    Card* predicted_card = getCard(deck_pointer, prediction);
    printf("I predict your card to be: ");
    printCard(predicted_card);
    printf("\n");

    //free everything
    empty(deck_pointer);
    free(deck_pointer);

    return 0;
}
