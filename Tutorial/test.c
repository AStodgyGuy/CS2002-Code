#include <stdio.h>

int main() {
	int pixel = 2;
	printf("pixel before bitwise operator = %d\n", pixel);
	pixel ^= ~0;
	printf("pixel after bitwise operator = %d\n", pixel);
}
