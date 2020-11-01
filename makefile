CC=gcc
CFLAGS=-Wall -Wextra -Werror -lm

all : hist_equalization sobel negative

hist_equalization: hist_equalization.c
	$(CC) hist_equalization.c -o bin/hist_equalization $(CFLAGS)
	bin/hist_equalization

sobel: sobel.c
	$(CC) sobel.c -o bin/sobel $(CFLAGS)
	bin/sobel

negative: negative.c
	$(CC) negative.c -o bin/negative $(CFLAGS)
	bin/negative

clean:
	@rm *.o bin/*

.PHONY: clean hist_equalization test