#include"pado.h"
#include<stdio.h>

int first, second, third;

int padocalc(int n)
{
    if (n == 0) {
        return first;
    } else if (n == 1) {
        return second;
    } else if (n == 2) {
        return third;
    }

    int arr[n];

    arr[0] = first;
    arr[1] = second;
    arr[2] = third;

    for(int i = 3; i <= n; i++) {
        arr[i] = arr[i-2] + arr[i-3];
    }
    
    return arr[n];
}
