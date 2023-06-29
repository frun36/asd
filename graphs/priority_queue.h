#ifndef _PRIORITY_QUEUE
#define _PRIORITY_QUEUE

#include <stddef.h>

#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)
#define HEAP_MIN(heap) (heap[1])

typedef struct tpq_node {
    void *data;
    size_t data_size;
    int key;
} pq_node;

void swap(void *a, void *b, size_t size);

pq_node *pq_allocate(size_t len);
void min_heapify(pq_node *heap, size_t heap_size, size_t i);
size_t pq_build(pq_node *heap, size_t len);
pq_node pq_extract_min(pq_node *queue, size_t *heap_size);
void pq_decrease_key(pq_node *queue, size_t i, int key);
void pq_insert(pq_node *queue, size_t *heap_size, pq_node node);

#endif