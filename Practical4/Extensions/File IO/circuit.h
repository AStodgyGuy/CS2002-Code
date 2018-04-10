#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Typedef struct for a wire
 */
typedef struct Wire {
    int current_value;
    int previous_value;
    char* name;
    bool is_in;
    struct Wire* next;
} Wire;

/*
 * Typedef struct for a gate
 */
typedef struct Gate {
    Wire* input_one;
    Wire* input_two;
    Wire* output;
    char* type;
    struct Gate* next; 
} Gate;

/**
 * Typedef struct for a linked list of wires
 */
typedef struct WireList {
    struct Wire* head;
    struct Wire* tail;
    int size;
} WireList;

/**
 * Typedef struct for a linked list of gates
 */
typedef struct GateList {
    struct Gate* head;
    struct Gate* tail;
    int size;
} GateList;

void addToWireList(Wire* wire_to_add, WireList* wirelist);
bool checkIfWireExists(char* name, WireList* wirelist);
void addToGateList(Gate* gate, GateList* gatelist);
Wire* getWireLocation(char* wire_to_get, WireList* wirelist);
void freeGateList(GateList* gatelist);
void freeWireList(WireList* wirelist);
void initialiseAllWiresToZero(WireList* wirelist);
void initialiseDefaultWires(WireList* wirelist);
void evaluateGates(GateList* gatelist);
void updateWires(WireList* wirelist);
int getNumberOfInWires(WireList* wirelist);