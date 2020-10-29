CC=gcc
#CFLAGS=-Wall -Wextra -Werror
CFLAGS=

all : main

main: main.c
	$(CC) main.c -o main $(CFLAGS)
	./main

test: test.c
	$(CC) test.c -o test $(CFLAGS)
	./test

clean:
	rm *.o

.PHONY: clean main test