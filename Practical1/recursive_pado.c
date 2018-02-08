#include "pado.h"

/**
 * A method which calculates Padovan numbers recursively
 */
int padocalc(int n) 
{
    if (n < 3) {
        return 1;
    } 
    else {
        return padocalc(n-2) + padocalc(n-3);
    }
}