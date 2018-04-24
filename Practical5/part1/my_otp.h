#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

void process(char* IN_PATH, char* OUT_PATH, char* KEY_PATH);
void chkfork(int child1);
void chkin(char* INPUT_PATH, char* OUT_PATH, char* KEY_PATH);