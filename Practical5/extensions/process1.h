#ifndef PROCESS1_HEADER
#define PROCESS1_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cipher(int c, FILE* KEY_PATH);
void pcipher(char* KEY_PATH, char* IN_PATH, int* fd);

#endif

