#include "circuit.h"

/**
 * Method to create a wire and add it to the list of wires
 */
void createWire(char* line, WireList* wirelist, bool is_user_defined) {
    //check if wire already exists in the wire list
    Wire* new_wire = malloc(sizeof(Wire));
    if (!checkIfWireExists(line, wirelist)) {
        //doesn't exist, create a new wire
        new_wire->name = malloc(strlen(line) + 1);
        strcpy(new_wire->name, line);
        new_wire->is_user_defined = is_user_defined;
        addToWireList(new_wire, wirelist);
    } else {
        //else free the malloc
        free(new_wire);
    }
}
/**
 * Method to create a gate and add it to the list of wires
 */
void createGate(char* gate_type, char* first_input_wire, char* second_input_wire, char* output_wire, GateList* gatelist, WireList* wirelist) {      
    //check if wire already exists in the wire list
    Gate* new_gate = malloc(sizeof(Gate));
    new_gate->type = malloc(strlen(gate_type)+1);
    strcpy(new_gate->type, gate_type);
    new_gate->input_one = getWireLocation(first_input_wire, wirelist);
    //if input two is null then add an input two wire
    if (second_input_wire == NULL) {
        Wire* wire = malloc(sizeof(Wire));
        wire->current_value = 0;
        wire->previous_value = 0;      
    } else {
        new_gate->input_two = getWireLocation(second_input_wire, wirelist);
    }
    new_gate->output = getWireLocation(output_wire, wirelist);

    addToGateList(new_gate, gatelist);
}

/**
 * Method to process three inputs from input file
 */
void processThreeInputs(char* line, WireList* wirelist, GateList* gatelist) {
    char s[4] = " \n";
    char* output_wire;
    char* gate_type;
    char* input_wire;
    char* token;
    
    token = strtok(line, s);
    for (int i = 0; i < 3; ++i) {
        switch (i) {
            case 0:
                output_wire = malloc(strlen(token) + 1);
                strcpy(output_wire, token);
                createWire(output_wire, wirelist, false);
                break;
            case 1:
                gate_type = malloc(strlen(token) + 1);
                strcpy(gate_type, token);
                break;
            case 2:
                input_wire = malloc(strlen(token) + 1);
                strcpy(input_wire, token);
                createWire(input_wire, wirelist, false);
                break;
        }
        token = strtok (NULL, s);
    }

    //after wire is created a gate exists
    createGate(gate_type, input_wire, NULL, output_wire, gatelist, wirelist);
    free(output_wire);
    free(gate_type);
    free(input_wire);
}

/**
 * Method to process four inputs from input file
 */
void processFourInputs(char* line, WireList* wirelist, GateList* gatelist) {
    char s[4] = " \n";
    char* output_wire;
    char* gate_type;
    char* first_input_wire;
    char* second_input_wire;
    char* token;
    
    token = strtok(line, s);

    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0:
                output_wire = malloc(strlen(token) + 1);
                strcpy(output_wire, token);
                createWire(output_wire, wirelist, false);
                break;
            case 1:
                gate_type = malloc(strlen(token) + 1);
                strcpy(gate_type, token);
                break;
            case 2:
                first_input_wire = malloc(strlen(token) + 1);
                strcpy(first_input_wire, token);
                createWire(first_input_wire, wirelist, false);
                break;
            case 3:
                second_input_wire = malloc(strlen(token) + 1);
                strcpy(second_input_wire, token);
                createWire(second_input_wire, wirelist, false);
                break;

        }
        token = strtok (NULL, s);
    }

    //after wire is created a gate exists
    createGate(gate_type, first_input_wire, second_input_wire, output_wire, gatelist, wirelist);
    free(output_wire);
    free(gate_type);
    free(first_input_wire);
    free(second_input_wire);
}

/**
 * Method to process lines in the file
 */
void processLine(char* line, WireList* wirelist, GateList* gatelist) { 
    int no_of_inputs = 0;
    char s[4] = " \n";
    int len = strlen(line);
    char lastC;
    char* token;
    char* name;

    // check number of inputs
    if (len > 0) {
        lastC = line[0];
    }

    //calculate number of inputs
    for (int i = 0; i <= len; ++i) {
        if ((line[i] == ' ' || line[i] == '\0') && lastC != ' ') {
            ++no_of_inputs;
        }
        lastC = line[i];
    }

    // switch statement depending on how inputs there are can be either 2 , 3 or 4
    switch (no_of_inputs) {
        case 2:
            // {wire} {IN}
            token = strtok(line, s);
            name = malloc(strlen(token) + 1);
            strcpy(name, token);
            createWire(name, wirelist, true);
            free(name);
            break;
        case 3:
            // {wire} {GATE} {wire} 
            processThreeInputs(line, wirelist, gatelist);
            break;
        case 4:
            // {wire} {GATE} {wire} {wire}
            processFourInputs(line, wirelist, gatelist);
            break;
        default:
            return;
    }
}

/*
 * Method which process the file contents into structure
 * that can be used to generate truth tables 
 */
void processFileLocation(FILE *file_ptr, WireList* wirelist, GateList* gatelist) {
    char buf[1000];
    int i = 0;

    //obtain line by line of each file
    while (1) {
        if (fgets(buf,1000, file_ptr) == NULL) break;
        ++i;
        processLine(buf, wirelist, gatelist);
    }
}

/*
 * Method which reads a file from a file location
 */
void readFileLocation(char* file_location, WireList* wirelist, GateList* gatelist) {
    FILE *file_ptr;
    file_ptr = fopen(file_location,"r");
    if (!file_ptr)
        return;
    processFileLocation(file_ptr, wirelist, gatelist);
    fclose(file_ptr);
    return;
}

/**
 * Debug method which prints the time table for wires
 */
void printTable(int rows, int columns, int array[][columns]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Method to calculate the power of something
 */ 
int powerOf(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result = result * base;
    }
    return result;
}

/**
 * Method to calculate the bianry value of a number represented in n bits
 */
void convertToBinary(int* result_array, int no_to_convert, int no_of_bits) {
    int temp = no_to_convert % 2;
    for (int i = no_of_bits - 1; i > -1 ; --i) {
        result_array[i] = temp;
        no_to_convert = no_to_convert / 2;
        temp = no_to_convert % 2;
    }
}

/**
 * Method to calculate all possible permutations of {0,1} given n wires
 */
void calculateAllPermutations(int rows, int columns, int array[][columns]) {
    int binary[columns];
    memset(binary, 0, columns*sizeof(int));
    for (int i = 0; i < rows; ++i) {
        //convert the number to binary to obtain all possible permutations
        convertToBinary(binary, i, columns);
        for (int j = 0; j < columns; ++j) {
            array[i][j] = binary[j];
        }
    }
}

/**
 * Method to permutate the inputs of the input wires
 */
void permuteInputs(WireList* wirelist, int column_to_calculate, int columns, int array[][columns]) {
    int size = wirelist->size;
    int col = 0;
    Wire* current_wire = wirelist->head;
    while (size > 0) {
        if (current_wire->is_user_defined) {
            current_wire->current_value = array[column_to_calculate][col];
            ++col;
        }
        --size;
        current_wire = current_wire->next;
    }
}

/**
 * Method to calculate number of possible permutations of wires
 */
int calculateNoOfPossiblePermutations(int no_of_wires) {
    //2^n possible combinations
    return powerOf(2, no_of_wires);
}

/**
 * Debug method to verify that printing permutations is correct
 */
void printPermutations(int rows, int columns, int array[][columns]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

/**
 * Method to generate output table
 */
void generateOutputTable(WireList* wirelist, int current_time, int columns, int output[][columns]) {
    //check if out wire exists
    if (checkIfWireExists("out", wirelist)) {
        output[0][current_time] = getWireLocation("out", wirelist)->current_value;
    } else {
        int size = wirelist->size;
        int temp = 0;
        Wire* current_wire = wirelist->head;
        while (size > 0) {
            output[temp][current_time] = current_wire->current_value;
            current_wire = current_wire->next;
            ++temp;
            --size;
        }
    }
}

/**
 * Method to check whether a circuit is stable or not
 */
int checkStable(WireList* wirelist, int out_col, int out_row, int out_table[][out_col]) {
    
    //out exists, out wire is on the 0 row of the out table
    int i, j;
    if (checkIfWireExists("out", wirelist)) {
        if (out_table[0][out_col - 1] == out_table[0][out_col - 2]) {
            return out_table[0][out_col-1];
        } else {
            return 2;
        }
        
    //out wire does not exist, check all wires
    } else {
        for (i = 0; i < out_row; ++i) {
            for (j = 2; j < out_col; ++j) {
                if (out_table[i][j] != out_table[i][j-1]) {
                    return 2;
                }
            }
        }
        return 0;
    }
}

/**
 * Method to write results to a file
 */
void writeResults(WireList* wirelist, int perm_col, int current_combin, int perm_array[][perm_col], char* output_path, int result) {
    //open file
    FILE* file  = fopen(output_path,"a");

    //write headers for wires and out if there is an out wire
    if (current_combin == 0) {
        int temp = wirelist->size;
        Wire* current_wire = wirelist->head;    
        while(temp > 0) {
            if (current_wire->is_user_defined || strcmp(current_wire->name, "out") == 0) {
                fprintf(file, "%s ", current_wire->name);
                fflush(file);
            }
            --temp;
            current_wire = current_wire->next;
        }
        fprintf(file, "\n");
        fflush(file);
        
    }
    //write out permutation
    for (int i = 0; i < perm_col; ++i) {
        fprintf(file, "%d ", perm_array[current_combin][i]);
        fflush(file);
    }

    //write out stabilization result
    switch (result) {
        case 0:
            fprintf(file, "0\n");
            fflush(file);
            break;
        case 1:
            fprintf(file, "1\n");
            fflush(file);
            break;
        case 2:
            fprintf(file, "?\n");
            fflush(file);
            break;
    }
    fclose(file);
}

/**
 * Method to print results
 */
void printResults(WireList* wirelist, int perm_col, int current_combin, int perm_array[][perm_col], int result) {
    
    //print headers for wires and out if there is an out wire
    if (current_combin == 0) {
        int temp = wirelist->size;
        Wire* current_wire = wirelist->head;    
        while(temp > 0) {
            if (current_wire->is_user_defined || strcmp(current_wire->name, "out") == 0) {
                printf("%s ", current_wire->name);
            }
            --temp;
            current_wire = current_wire->next;
        }
        printf("\n");  
    }

    //print out permutation
    for (int i = 0; i < perm_col; ++i) {
        printf("%d ", perm_array[current_combin][i]);
    }

    //print out stabilization result
    switch (result) {
        case 0:
            printf("0\n");
            break;
        case 1:
            printf("1\n");
            break;
        case 2:
            printf("?\n");
            break;
    }
}

/**
 * Method to simulate circuit and produce output table
 */
void simualteCircuit(WireList* wirelist, GateList* gatelist, char* output_path) {
    //circuit stability result
    int result;

    //there are 2^(number of wires) + 2 times, the + 1 exists for initialising all gates to 0, and another +1 exists for default gates
    int max_time = powerOf(2, wirelist->size) + 2;

    //calculating table for inputs
    int no_defined_wires = getNumberOfUserDefinedWires(wirelist);
    int no_combin = calculateNoOfPossiblePermutations(no_defined_wires);
    int perm_array[no_combin][no_defined_wires];
    calculateAllPermutations(no_combin, no_defined_wires, perm_array);
    //printPermutations(no_combin, no_defined_wires, perm_array);

    //2D array for output table
    int out_table[wirelist->size][max_time];
    memset(out_table, 0, wirelist->size*max_time*sizeof(int));

    //loop through each combinaion
    for (int i = 0; i < no_combin; i++) {
        //loop through every time
        for (int current_time = 0; current_time < max_time; ++current_time) { 
            //at t = -1, initialise all wires to zero
            if (current_time == 0) {
                initialiseAllWiresToZero(wirelist);
            //at t = 0, initialise all default values to default values
            } else if (current_time == 1) {
                initialiseDefaultWires(wirelist);
                permuteInputs(wirelist, i, no_defined_wires, perm_array);
            //at t = anyhting else, evaluate all gates to obtain output
            } else {
                //permutation of wire inputs goes here
                if (current_time > 2) {
                    updateWires(wirelist);
                }
                evaluateGates(gatelist);
            }
            //generate output table
            generateOutputTable(wirelist, current_time, max_time, out_table);
        }
        //check whether output table is stable or not
        result = checkStable(wirelist, max_time, wirelist->size, out_table);
        //write to output path
        if (output_path == NULL) {
            printResults(wirelist, no_defined_wires, i, perm_array, result);
        } else {
            writeResults(wirelist, no_defined_wires, i, perm_array, output_path, result);
        }
    }
}


/**
 * Main method
 */
int main(int argc, char *argv[])
{
    //defining list of wires
    WireList* wirelist = malloc(sizeof(WireList));
    wirelist->head = NULL;
    wirelist->tail = NULL;
    wirelist->size = 0;

    //deifining list of gates
    GateList* gatelist = malloc(sizeof(GateList));
    gatelist->head = NULL;
    gatelist->tail = NULL;
    gatelist->size = 0;

    //creating default wire 'one'
    Wire* one = malloc(sizeof(Wire));
    one->name = "one";
    one->is_user_defined = false;
    one->current_value = 1;
    one->previous_value = 1;
    addToWireList(one, wirelist);

    //creating default wire 'zero'
    Wire* zero = malloc(sizeof(Wire));
    zero->name = "zero";
    zero->is_user_defined = false;
    zero->current_value = 0;
    zero->previous_value = 0;
    addToWireList(zero, wirelist);

    if (argc == 1) {
        char* output_path = NULL;
        char s[200];
        while(scanf("%[^\n]%*c",s)==1){
            processLine(s, wirelist, gatelist);
        }
        simualteCircuit(wirelist, gatelist, output_path);

    // user specifies an output path
    } else if (argc == 2) {
        //read line by line
        char* output_path = argv[1];
        char s[200];
        while(scanf("%[^\n]%*c",s)==1){
            processLine(s, wirelist, gatelist);
        }
        simualteCircuit(wirelist, gatelist, output_path);

    // user specifies both an input and output path
    } else if (argc ==3) {
        char* input_path = argv[1];
        char* output_path = argv[2];
        //evaluate all lines of the input.txt file as code
        readFileLocation(input_path, wirelist, gatelist);
        //run circuit with all possible combinations for user defined wires to generate stability table
        //write results to output_path
        simualteCircuit(wirelist, gatelist, output_path);
    } else {
        printf("%d\n", argc);
        printf("Error! Program requires 2 .txt files as arguments\n");
        printf("Run with ./circuits input.txt output.txt\n or run with ./circuits < input.txt  output.txt\n or with ./circuits < input.txt > output.txt\n");
        return 0;
    }
    //free everything
    freeGateList(gatelist);
    freeWireList(wirelist);
    return 0;
}

