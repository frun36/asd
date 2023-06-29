#include "fifo.h"

Fifo *fifo_init(size_t capacity) {
    if (capacity < 2) {
        fprintf(stderr, "Capacity of FIFO queue must be larger that 1\n");
        return NULL;
    }
    Fifo *fifo = malloc(sizeof(Fifo) + capacity * sizeof(void *));
    fifo->capacity = capacity;
    fifo->begin = 0;
    fifo->end = 0;
    return fifo;
}

void fifo_enqueue(Fifo *fifo, void *data) {
    if (fifo->begin == fifo->end && fifo->queue[fifo->begin] != NULL) {
        fprintf(stderr, "Couldn't enqueue item: queue full\n");
        return;
    }
    fifo->queue[fifo->end] = data;
    fifo->end = (fifo->end + 1) % fifo->capacity;
}

void *fifo_dequeue(Fifo *fifo) {
    if (fifo->queue[fifo->begin] == NULL) {
        fprintf(stderr, "Couldn't dequeue item: queue empty\n");
    }
    void *data = fifo->queue[fifo->begin];
    fifo->queue[fifo->begin] = NULL;
    fifo->begin = (fifo->begin + 1) % fifo->capacity;
    return data;
}

void fifo_print(Fifo *fifo, printData print_data) {
    for (size_t i = 0; i < fifo->capacity; i++) {
        printf("%3lu", i);
        if (i == fifo->begin && i == fifo->end) {
            printf(" be: ");
        } else if (i == fifo->begin) {
            printf("  b: ");
        } else if (i == fifo->end) {
            printf("  e: ");
        } else {
            printf("   : ");
        }
        if (print_data) {
            print_data(fifo->queue[i]);
        } else {
            printf("\n");
        }
    }
    printf("-----\n");
}

void fifo_free(Fifo **fifo, freeData free_data) {
    if (fifo && *fifo) {
        if (free_data) {
            for (size_t i = 0; i < (*fifo)->capacity; i++) {
                free_data((*fifo)->queue[i]);
            }
        }
        free(*fifo);
        *fifo = NULL;
    }
}