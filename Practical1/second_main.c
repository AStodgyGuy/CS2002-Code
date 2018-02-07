#include<stdio.h>
#include<stdbool.h>
#include"pado.h"
#define MAX_INT 2147483647

bool is_overflow(int first, int second, int third);
bool get_valid_starting_inputs();
bool get_valid_length_input();
int num;

int main(void)
{

    while (true) {

        //check for valid starting inputs
        if (get_valid_starting_inputs()) {
            //check for valid length input
            if (get_valid_length_input()) {
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
            } else {
                break;
            }
        } else {
            break;
        } 
   }

    return 0;
}

/**
 * Method to check for overflow
 */
bool is_overflow(int first, int second, int third) 
{
    if(first > MAX_INT || second > MAX_INT || third > MAX_INT) {
        return true;
    } else {
        return false;
    }
}

/**
 * Method which returns a boolean based on whether the input is valid or not
 */
bool get_valid_starting_inputs() 
{
    extern int first, second, third;

    //get starting inputs
    printf("Starting values? ");
    if (scanf("%d,%d,%d", &first, &second, &third) != 3) {  //checking for valid input
        printf("Invalid input\n");
        return false;
    }

    //check validated inputs for 0 values
    if (first == 0 && second == 0 && third == 0) {
        return false;
    }

    //check validated inputs for overflow values
    if (is_overflow(first, second, third)) {
        printf("Overflow\n");
        return false;
    }

    return true;
}

/**
 * Method which returns a boolean based on whether the input is valid or not
 */
bool get_valid_length_input() 
{
    //how many numbers to generate
    printf("Length? ");
    if (scanf("%d", &num) != 1) {   //checking for valid input
        printf("Invalid input\n");
        return false;
    }

    //check overflow
    if (is_overflow(num, 0, 0)) {
        printf("Overflow\n");
        return false;
    }
    return true;
}
