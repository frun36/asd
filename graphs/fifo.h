#include <stdio.h>
#include <stdlib.h>

typedef void (*printData)(void *);
typedef void (*freeData)(void *);

typedef struct _Fifo {
    size_t capacity;
    size_t begin;
    size_t end;
    void *queue[];
} Fifo;

Fifo *fifo_init(size_t);
void fifo_enqueue(Fifo *, void *);
void *fifo_dequeue(Fifo *);
void fifo_print(Fifo *, printData);
void fifo_free(Fifo **, freeData);