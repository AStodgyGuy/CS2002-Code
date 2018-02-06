#include<stdio.h>
#include "pado.h"

int main() 
{
    int num;
    int i;
    //print prompt length
    printf("Length? ");
    //read integer
    scanf("%d", &num);
    int list[num];
    //print the first n elements of the padovan sequence
    for(int i = 0; i < num; i++) {
        list[i] = padocalc(i);
    }

    if (sizeof(list) > 0) {
        printf("[");
        for(int j = 0; j < num-1; j++) {
            printf("%d, ",list[j]);
        }
        printf("%d", list[num-1]);
        printf("]\n");
    } else {
        printf("[]");
    }

    return 0;

}