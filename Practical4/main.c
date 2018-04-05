#include "readfile.h"

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        printf("Error! Program requires 2 arguments\n");
        return 0;
    } else {
        char* input_path = argv[1];
        char* output_path = argv[2];
        //process input path
        readFileLocation(input_path);
        //calculate truth table
        //output truth table to output path
    }
}

