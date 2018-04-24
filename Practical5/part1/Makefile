CC = clang
CFLAGS = -Wall -Wextra -g3

main: my_otp.h process1.h process2.h
	${CC} ${CFLAGS} my_otp.c process1.c process2.c -o my_otp

process1: process1.h
	${CC} ${CFLAGS} process1.c -o process1

process2: process2.h
	${CC} ${CFLAGS} process2.c -o process2

clean:
	rm -rf my_otp process1 process2