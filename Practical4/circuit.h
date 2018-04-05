/*
 * Typedef struct for a gate
 */
typedef struct Gate {
    char first_input_wire[50];
    char second_input_wire[50];
    char output_wire[50];
    enum gate_type{NOT, AND, NAND, OR, NOR, XOR,EQ};
} Gate;

/**
 * Typedef struct for a wire
 */
typedef struct Wire {
    char name[50];
    int value;
} Wire;

/**
 * Typedef struct for a vertice
 * A vertice is a node in a graph
 */
typedef struct Vertice {
    union {
        struct Gate gate;
        struct Wire wire;
    } node_type;

    
} Vertice;

