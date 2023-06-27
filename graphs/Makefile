CC = gcc
CFLAGS = -Wall -Wextra -g
DEPS = list.h directed.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

graphs: list.o directed.o  graphs.c
	$(CC) -o graphs list.o directed.o graphs.c