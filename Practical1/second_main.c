#include<stdio.h>
#include<stdbool.h>
#include"pado.h"
#define MAX_INT 2147483647

bool is_overflow(int first, int second, int third);
extern void setglobalvars(int first, int second, int third);

int main(void)
{
    extern int first, second, third;
    
    int num;

    while (true) {

        //get starting inputs
        printf("Starting values? ");
        if (scanf("%d,%d,%d", &first, &second, &third) != 3) {  //checking for valid input
            printf("Invalid input\n");
            break;
        }

        //check validated inputs for 0 values
        if (first == 0 && second == 0 && third == 0) {
            break;
        }

        //check validated inputs for overflow values
        if (is_overflow(first, second, third)) {
            printf("Overflow\n");
            break;
        }

        //set global vars for pado calc
        setglobalvars(first, second, third);

        //how many numbers to generate
        printf("Length? ");
        if (scanf("%d", &num) != 1) {   //checking for valid input
            printf("Invalid input\n");
            break;
        }

        //check overflow
        if (is_overflow(num, 0, 0)) {
            printf("Invalid input\n");
            break;
        }

        //calculate all numbers
        int list[num];
        for(int i = 0; i < num; i++) {
            list[i] = padocalc(i);
        }

        //print all numbers
        if (sizeof(list) > 0) {
            printf("[");
            for(int j = 0; j < num-1; j++) {
                printf("%d, ",list[j]);
            }
            printf("%d", list[num-1]);
            printf("]\n");
        } else {
            printf("[]\n");
        }

    }

    return 0;
}

/**
 * Method to check for overflow
 */
bool is_overflow(int first, int second, int third) {
    if(first > MAX_INT || second > MAX_INT || third > MAX_INT) {
        return true;
    } else {
        return false;
    }
}
