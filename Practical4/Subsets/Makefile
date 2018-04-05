CC = clang
FLAGS = -Wall -Wextra -O0

all: subsets
clean:
	rm -f subsets

subsets: subsets.c
	${CC} ${FLAGS} subsets.c -o subsets
