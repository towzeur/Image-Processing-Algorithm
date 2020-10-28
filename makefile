CC=gcc
CFLAGS=-Wall -Wextra -Werror

all : main

main.o : main.c
	$(CC) -c main.c -o main.o

main: main.o
	$(CC) main.o -o main
	./main

.PHONY: clean main

clean:
	rm *.o
