/**
 * Card struct definiton for queue
 */

typedef struct Card {
    int rank;
    int suit;
    struct Card* next;
} Card;
