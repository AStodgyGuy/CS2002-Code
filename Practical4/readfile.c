#include "readfile.h"

/*
 * Method which reads a file from a file location
 */
void readFileLocation(char* file_location) {
    FILE *file_ptr;

    file_ptr =fopen(file_location,"r");
    if (!file_ptr)
        return;

    processFileLocation(file_ptr);

    fclose(file_ptr);
    return;
}

/*
 * Method which process the file contents into structure
 * that can be used to generate truth tables 
 */
void processFileLocation(FILE *file_ptr) {
    char buf[1000];
    int i = 0;

    //obtain line by line of each file
    while (1) {
        if (fgets(buf,1000, file_ptr) == NULL) break;
        i++;
        processLine(buf);
    }
}

/**
 * Method to process lines in the file
 */
void processLine(char* line) { 
    
}

