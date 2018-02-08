#include<limits.h>
#include<stdio.h>
#include<stdbool.h>
#include"pado.h"

extern int padocalc(int i);
bool is_overflow(long long value);
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
                if (num > 0) {
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
 * Method which returns a boolean based on whether the input is valid or not
 */
bool get_valid_starting_inputs() 
{
    long long tempfirst, tempsecond, tempthird;
    extern int first, second, third;

    //get starting inputs
    printf("Starting values? ");
    if (scanf("%lld,%lld,%lld", &tempfirst, &tempsecond, &tempthird) != 3) {  //checking for valid input
        printf("Invalid input\n");
        return false;
    }

    //check validated inputs for overflow values
    if (is_overflow(tempfirst) || is_overflow(tempsecond) || is_overflow(tempthird)) {
        printf("Overflow\n");
        return false;
    }

    first = (int) tempfirst;
    second = (int) tempsecond;
    third = (int) tempthird;

    //check for negative values
    if (first < 0 || second < 0 || third < 0) {
        printf("Invalid input\n");
        return false;
    }

    //check validated inputs for 0s
    if (first == 0 && second == 0 && third == 0) {
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
    if (is_overflow(num)) {
        printf("Overflow\n");
        return false;
    }
    return true;
}
