#include "circuit.h"

/**
 * Method to add a wire to the wire list
 */
void addToWireList(Wire* wire_to_add, WireList* wirelist) {
    if (wirelist->head == NULL) {
        wirelist->head = wirelist->tail = wire_to_add;
        ++wirelist->size;
        return;
    }
    wirelist->tail->next = wire_to_add;
    wirelist->tail = wire_to_add;
    wirelist->tail->next = NULL;
    ++wirelist->size;
}

/**
 * Method to check whether a wire already exists in the wire list or not
 */
bool checkIfWireExists(char* name, WireList* wirelist) {
    int size = wirelist->size;
    if (size == 0) {
        return false;
    }

    Wire* current_wire = wirelist->head;

    while (size > 0) {
        if (strcmp(name, current_wire->name) == 0) {
            return true;
        }
        --size;
        if (size == 0) {
            return false;
        } else {
            current_wire = current_wire->next;
        }
    }
    return false;
}

/**
 * Method to add a gate to the gate list
 */
void addToGateList(Gate* gate_to_add, GateList* gatelist) {
    if (gatelist->head == NULL) {
        gatelist->head = gatelist->tail = gate_to_add;
        ++gatelist->size;
        return;
    }
    gatelist->tail->next = gate_to_add;
    gatelist->tail = gate_to_add;
    gatelist->tail->next = NULL;
    ++gatelist->size;
}

/**
 * Method to get the memory location of a wire
 */
Wire* getWireLocation(char* wire_to_get, WireList* wirelist) {
    Wire* current_wire = wirelist->head;
    int size = wirelist->size;
    if (size == 0) {
        return NULL;
    }
    while (size > 0) {
        if (strcmp(wire_to_get, current_wire->name) == 0) {
            return current_wire; 
        }
        
        if (size == -1) {
            return NULL;
        } else {
            current_wire = current_wire->next;
        };
        --size;
    }
    return NULL;
}

/**
 * Method to free all elements in gatelist and the gatelist pointer
 */
void freeGateList(GateList* gatelist) {
    int size = gatelist->size;
    if (gatelist == 0) {
        return;
    }
    Gate* gate_to_free = gatelist->head;
    while (size > 0) {
        if (gatelist->head == gatelist->tail) {
            gatelist->head = gatelist->tail = NULL;
        } else {
            gatelist->head = gatelist->head->next;
        }
        free(gate_to_free->type);
        free(gate_to_free);
        gate_to_free = gatelist->head;
        --size;
    }
    free(gatelist);
}

/**
 * Method to free all elements in the wirelist and the wirelist pointer
 */
void freeWireList(WireList* wirelist) {
    int size = wirelist->size;
    if (size == 0) {
        return;
    }
    //freeing wire 'one'
    Wire* wire_to_free = wirelist->head;
    wirelist->head = wirelist->head->next;
    free(wire_to_free);
    --size;

    //freeing wire 'zero'
    wire_to_free = wirelist->head;
    wirelist->head = wirelist->head->next;
    free(wire_to_free);
    --size;

    //freeing the rest of the wires
    wire_to_free = wirelist->head;
    while (size > 0) {
        if (wirelist->head == wirelist->tail) {
            wirelist->head = wirelist->tail = NULL;
            
        } else {
            wirelist->head = wirelist->head->next;
        }
        free(wire_to_free->name);
        free(wire_to_free);
        wire_to_free = wirelist->head;
        
        --size;
    }
    free(wirelist);
}

//Calculate output of a gate given its input wires and type of gate
int calculateOutput(char* gate_type, Wire* first_input, Wire* second_input) {
    //not gate in code
    if (strcmp(gate_type, "NOT") == 0) {
        return (first_input->previous_value == 1) ? 0 : 1;

    //and gate in code
    } else if (strcmp(gate_type, "AND") == 0) {
        return (first_input->previous_value == 1 && second_input->previous_value == 1) ? 1 : 0;
    
    //nand gate in code
    } else if (strcmp(gate_type, "NAND") == 0) {
        return (first_input->previous_value == 1 && second_input->previous_value == 1) ? 0 : 1;

    //or gate in code
    } else if (strcmp(gate_type, "OR") == 0) {
        return (first_input->previous_value == 0 && second_input->previous_value == 0) ? 0 : 1;

    //nor gate in code
    } else if (strcmp(gate_type, "NOR") == 0) {
        return (first_input->previous_value == 0 && second_input->previous_value == 0) ? 1 : 0;

    //xor gate in code
    } else if (strcmp(gate_type, "XOR") == 0) {
        if (first_input->previous_value == 0 && second_input->previous_value == 1) {
            return 1;
        } else if (first_input->previous_value == 1 && second_input->previous_value == 0) {
            return 1;
        } else {
            return 0;
        }

    //implication gate in code
    } else if (strcmp(gate_type, "EQ") == 0) {
        return (first_input->previous_value == 1 && second_input->previous_value == 0) ? 0 : 1;

    //if someting goes wrong return -1
    } else {
        return -1;
    }
}

/**
 * At t = 0, initialise all wires to zero
 */
void initialiseAllWiresToZero(WireList* wirelist) {
    Wire* current_wire = wirelist->head;
    int size = wirelist->size;
    while (size > 0) {
        current_wire->previous_value = 0;
        current_wire->current_value = 0;
        current_wire = current_wire->next;
        --size;
    }
}

/**
 * At t = 1, initialise default 'one' wire to 1
 */
void initialiseDefaultWires(WireList* wirelist) {
    wirelist->head->current_value = 1;
    wirelist->head->next->current_value = 0;
}

/**
 * Return the current value for a particular wire
 */
void evaluateGates(GateList* gatelist) {
    //for every gate in gatelist calculate its output
    Gate* current_gate = gatelist->head;
    int size = gatelist->size;
    while (size > 0) {
        current_gate->output->current_value = calculateOutput(current_gate->type, current_gate->input_one, current_gate->input_two);
        current_gate = current_gate->next;
        --size;
    }
}

/**
 * Updates the current values of a wire to its previous value
 */
void updateWires(WireList* wirelist) {
    Wire* current_wire = wirelist->head;
    int size = wirelist->size;
    while (size > 0) {
        current_wire->previous_value = current_wire->current_value;
        current_wire = current_wire->next;
        --size;
    }
}

/**
 * Method which returns the number of user defined "in" wires
 */
int getNumberOfInWires(WireList* wirelist) {
    int no_of_in = 0;
    Wire* current_wire = wirelist->head;
    int size = wirelist->size;
    while (size > 0) {
        if (current_wire->is_in) {
            ++no_of_in;
        }
        current_wire = current_wire->next;
        --size;
    }
    return no_of_in;
}