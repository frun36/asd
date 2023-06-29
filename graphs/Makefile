CC = gcc
CFLAGS = -Wall -Wextra -g
DEPS = list.h directed.h priority_queue.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

graphs: list.o directed.o priority_queue.o graphs.c
	$(CC) -o graphs list.o directed.o priority_queue.o graphs.c