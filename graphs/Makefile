CC = gcc
CFLAGS = -Wall -Wextra -g
DEPS = list.h directed.h fifo.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

graphs: list.o directed.o fifo.o graphs.c
	$(CC) -o graphs list.o directed.o fifo.o graphs.c