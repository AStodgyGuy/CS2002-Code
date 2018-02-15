#include <stdlib.h>
#include <string.h>

/* Assuming two consecutive subarrays are sorted, 
 * merge them into one sorted subarray.
 * arr: array of elements 
 * size: size of element
 * left: start index of first subarray
 * mid: end index of first subarray and start index of second subarray
 * right: end index of second subarray
 * comp: comparator of elements
 */
static void merge(void* arr, long size, long left, long mid, long right, 
		long (*comp)(const void*, const void*)) {
	long len = right-left;
	void* tmp = malloc(len * size);
	long p1 = left;
	long p2 = mid;
	long p3 = 0;
	while (p1 < mid || p2 < right) 
		if (p2 >= right || (p1 < mid && comp(arr + size * p1, arr + size * p2) <= 0))
			memcpy(tmp + size * p3++, arr + size * p1++, size);
		else
			memcpy(tmp + size * p3++, arr + size * p2++, size);
	memcpy(arr + size * left, tmp, len * size);
	free(tmp);
}

/* Sort subarray.
 * arr: array of elements
 * size: size of element
 * left: left index of subarray
 * right: right index of subarray
 * comp: comparator of elements
 */
static void sortsub(void* arr, long size, long left, long right, 
		long (*comp)(const void*, const void*)) {
	if (right - left > 1) {
		long mid = left + (right-left) / 2;
		sortsub(arr, size, left, mid, comp);
		sortsub(arr, size, mid, right, comp);
		merge(arr, size, left, mid, right, comp);
	}
}

/* Sort array.
 * arr: array of elements
 * size: size of element
 * len: number of elements
 * comp: comparator of elements
 */
void mergesort(void* arr, long size, long len, long (*comp)(const void*, const void*)) {
	sortsub(arr, size, 0, len, comp);
}
