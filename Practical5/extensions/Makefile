CC = clang
CFLAGS = -Wall -Wextra -g3 -pthread

all: server client

server: process1.h
	${CC} ${CFLAGS} server.c process1.c -o server

client: msg_queue.h process1.h
	${CC} ${CFLAGS} client.c process1.c msg_queue.c -o client

clean:
	rm client server