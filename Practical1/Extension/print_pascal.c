#include<limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pascal.h"

bool is_overflow(long long value)

int main(void) 
{
    long long input;
    int length, coef;

    //get user input
    printf("Enter number of pascal lines to generate: ");
    if(scanf("%lld", &input) != 1) {     //check for valid input
        printf("Invalid input\n");
        exit(0);
    }

    //check for input overflow
    if(is_overflow(input)) {
        printf("Overflow\n");
        exit(0);
    }

    //convert long long to int
    length = (int) input;

    //calculate pascal's triangle
    pascal_calc(length);

    return 0;
}

/**
 * Method which returns a boolean based on whether the input will overflow integer or not
 */
bool is_overflow(long long value)
{
    //minus the maximum representable value for int with the value passed into function
    long long temp = value - INT_MAX;
    //if greater than 0 then value is greater than INT_MAX hence overflow
    if(temp > 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Method for calculating and printing pascal numbesr
 */
void pascal_calc(int n) 
{
    long long coef; 

    for (int i = 0; i < n; i++) {
        printf("[");
        for (int j = 0 ; j <= i; j++) {
            if (j == 0 || i ==0) {
                coef = 1;
            } else {
                coef = coef*(i-j+1)/j;
            }

            if (j != i) {
                printf("%lld, ", coef);
            } else {
                printf("%lld",coef);
            }
            
        }
        printf("]\n");
    }
}
