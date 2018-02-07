#include <stdio.h>
#include <stdlib.h>
#include "pascal.h"

int main(void) 
{
    int length, coef;

    //get user input
    printf("Enter number of pascal lines to generate: ");
    if(scanf("%d", &length) != 1) {     //check for valid input
        printf("Invalid input\n");
        exit(0);
    }

    pascal_calc(length);

    return 0;
}

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
