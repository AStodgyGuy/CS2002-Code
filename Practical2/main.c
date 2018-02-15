#include <stdio.h>

#include "sort.h"

/* Compare two pointers to long.
 * Return negative if the first is smaller,
 * positive if the second is smaller,
 * 0 if they are equal.
 */
static long comp_long(const void *p, const void *q) {
	long pl = *(const long *)p;
	long ql = *(const long *)q;
	return pl - ql;
}

/* Test merge sort.
 */
int main(void) {
	long array[] = {10, 8, 3, 7, 1, 9, 6, 5, 2, 4};
	long size = sizeof(array[0]);
	long len = sizeof(array) / size;
	mergesort(array, size, len, &comp_long);
	for (int i = 0; i < len; i++)
		printf("%li\n", array[i]);
	return 0;
}
