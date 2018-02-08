#include<stdio.h>
#include"pado.h"

/**
 * Method which calculates Padovan numbers iteratively
 */
int padocalc(int n)
{
    if (n < 3) {
        return 1;
    }

    int arr[n];

    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 1;

    for(int i = 3; i <= n; i++) {
        arr[i] = arr[i-2] + arr[i-3];
    }
    
    return arr[n];
}