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
    printf("\n%d\t%d\t%d\n", 1, 2, 3);
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

//method to get a number from the user between 0 and 27
int getUserNumber() {
    int user_number;
    char initial_input[100];
    printf("Enter a number between 0 and 27 or enter 0 to exit: ");
    while(1) {
        scanf("%s", initial_input);
        if (sscanf(initial_input,"%d", &user_number)) {
            if (user_number >= 0 && user_number < 27) {
                break;
            }
        }
        printf("Invalid input! Enter a number between 0 and 27 or enter 0 to exit: ");
    }
    return user_number;   
}

//method which converts a number into base three
int* convertToBaseThree(int user_number) {
    static int base_three_array[3];
    int index = 0;
    int base = 3;
    while (user_number != 0) {
        base_three_array[index] = user_number % base;
        user_number = user_number / base;
        ++index;
    }

    return base_three_array;
}


//method to combine decks
Deck* combineDecks(Deck* deck, Deck* top_deck, Deck* middle_deck, Deck* bottom_deck) {
    int i = 0;
    int size_of_deck = top_deck->size;
    
    //dequeue all elements in column deck and enqueue it into the main deck
    while (i < size_of_deck) {
        enqueue(dequeue(top_deck), deck);
        i++;
    }

    i = 0;
    //dequeue all elements in column deck and enqueue it into the main deck
    while (i < size_of_deck) {
        enqueue(dequeue(middle_deck), deck);
        i++;
    }

    i = 0;
    //dequeue all elements in column deck and enqueue it into the main deck
    while (i < size_of_deck) {
        enqueue(dequeue(bottom_deck), deck);
        i++;
    }

    return deck;
}

Deck* switchDecks(int position, Deck* deck, Deck* deck_to_be_switched, Deck* other_deck, Deck* deck_other) {
    switch (position) {
        //put user selected deck to top of pile
        case 0:
            deck = combineDecks(deck, deck_to_be_switched, other_deck, deck_other);
            break;
        //put user selected deck to middle of pile
        case 1:
            deck = combineDecks(deck, deck_other, deck_to_be_switched, other_deck);
            break;
        //put user selected deck to bottom of pile
        case 2:
            deck = combineDecks(deck, other_deck, deck_other, deck_to_be_switched);
            break;
    }

    return deck;
}

//method to position the decks
Deck* positionDecks(int user_input, int position, Deck* deck, Deck* deck_one, Deck* deck_two, Deck* deck_three) {

    //get the user selected deck to switch
    switch (user_input) {
        case 1:
            deck = switchDecks(position, deck, deck_one, deck_two, deck_three);
            break;
        case 2:
            deck = switchDecks(position, deck, deck_two, deck_one, deck_three);
            break;
        case 3:
            deck = switchDecks(position, deck, deck_three, deck_one, deck_two);
            break;
    }

    return deck;
}

//method to collect the cards
Deck* collectDeck(Deck* deck, int user_input, int position) {

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

    //position the decks
    deck = positionDecks(user_input, position, deck, deck_one, deck_two, deck_three);

    //free the decks
    free(deck_one);
    free(deck_two);
    free(deck_three);

    //return the deck
    return deck;
}

//main method
int main() {
    int no_of_columns = 3;
    int no_of_rows = 9;
    int no_of_cards = no_of_columns * no_of_rows;
    int no_of_suits = 4;
    int no_of_ranks = 13;
    int no_of_repitions = 3;
    int user_number, user_input;
    int *pointer_to_base_three; 

    //pick a number between 0 and 27
    user_number = getUserNumber();
    if (user_number == 0) {
            //free everything
            printf("Exiting the program...\n");
            return 0;
    }

    //convert number into base three
    pointer_to_base_three = convertToBaseThree(user_number);

    //create deck of 27 random cards
    Deck* deck_pointer = malloc(sizeof(Deck));
    deck_pointer->front = NULL;
    deck_pointer->rear = NULL;
    deck_pointer->size = 0;
    deck_pointer = createDeck(deck_pointer, no_of_cards, no_of_suits, no_of_ranks);

    //display the cards
    printDeck(deck_pointer, no_of_rows, no_of_columns);

    //pick a card shown in one of the columns
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
        deck_pointer = collectDeck(deck_pointer, user_input, *(pointer_to_base_three + i));
        //print deck
        printDeck(deck_pointer, no_of_rows, no_of_columns);
    }

    //user's card is in the position the user chose
    Card* predicted_card = getCard(deck_pointer, user_number);
    printf("At the start I said to choose a number, and you chose %d\n", user_number);
    printf("Amazingly, through shuffling and manipulating the decks, I have put your card in that position\n");
    printf("Hence, I predict your card to be: ");
    printCard(predicted_card);
    printf("\n");

    //free everything
    empty(deck_pointer);
    free(deck_pointer);

    return 0;
}