#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main() {
	typedef struct test1{int i; char c;} test1;
	typedef union test2{char d; int i; char c;} test2;
	printf("%d\n", sizeof(test1));
	printf("%d\n", sizeof(test2));
}
