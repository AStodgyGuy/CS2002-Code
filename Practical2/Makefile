CC = clang
CFLAGS = -c -Wall -Wextra -O0
AFLAGS = -c -S -Wall -Wextra -fno-verbose-asm
LFLAGS = -Wall -Wextra

all: main main-plus sort0.s sort1.s sort2.s sort3.s sort-plus.s
clean:
	rm -f main main-plus *.o sort0.s sort1.s sort2.s sort3.s sort-plus.s

main: main.o sort.o
	${CC} ${LFLAGS} main.o sort.o -o main

main-plus: main.o sort-plus.o stack.o
	${CC} ${LFLAGS} main.o sort-plus.o stack.o -o main-plus

main.o: main.c
	${CC} ${CFLAGS} main.c -o main.o

sort.o: sort.c
	${CC} ${CFLAGS} sort.c -o sort.o

sort-plus.o: sort-plus.c
	${CC} ${CFLAGS} sort-plus.c -o sort-plus.o

stack.o: stack.c
	${CC} ${CFLAGS} stack.c -o stack.o

sort0.s: sort.c
	${CC} ${AFLAGS} -O0 sort.c -o sort0.s

sort1.s: sort.c
	${CC} ${AFLAGS} -O1 sort.c -o sort1.s

sort2.s: sort.c
	${CC} ${AFLAGS} -O2 sort.c -o sort2.s

sort3.s: sort.c
	${CC} ${AFLAGS} -O3 sort.c -o sort3.s

sort-plus.s: sort-plus.c
	${CC} ${AFLAGS} -O0 sort-plus.c -o sort-plus.s
