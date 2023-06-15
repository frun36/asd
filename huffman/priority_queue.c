#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "priority_queue.h"


void swap(void *a, void *b, size_t size) {
    char *p = (char *)a;
    char *q = (char *)b;
    char tmp = 0;
    for(size_t i = 0; i < size; i++) {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

pq_node *pq_allocate(size_t len) { 
    pq_node *p = malloc((len+1)*sizeof(pq_node));
    if(!p) {
        fprintf(stderr, "Error: Couldn't allocate queue.\n");
    }
    return p;
}

void min_heapify(pq_node *heap, size_t heap_size, size_t i) {
    size_t l = LEFT(i);
    size_t r = RIGHT(i);
    size_t min = i;
    while((l <= heap_size && heap[l].key < heap[min].key) || (r <= heap_size && heap[r].key < heap[min].key)) {
        if(l <= heap_size && heap[l].key < heap[min].key) {
            min = l;
        }
        if(r <= heap_size && heap[r].key < heap[min].key) {
            min = r;
        }
        if(min != i) {
            swap(heap+i, heap+min, sizeof(pq_node));
        }
        i = min;
        l = LEFT(i);
        r = RIGHT(i);
    }
    // if(l <= heap_size && heap[l].key < heap[min].key) {
    //     min = l;
    // }
    // if(r <= heap_size && heap[r].key < heap[min].key) {
    //     min = r;
    // }
    // if(min != i) {
    //     swap(heap+i, heap+min, sizeof(pq_node));
    //     min_heapify(heap, heap_size, min);
    // }
}

size_t pq_build(pq_node *heap, size_t len) {
    for(size_t i = len/2; i >= 1; i--) {
        min_heapify(heap, len, i);
    }
    return len;
}

pq_node pq_extract_min(pq_node *queue, size_t *heap_size) {
    if(*heap_size < 1) {
        fprintf(stderr, "Error: Heap is empty, cannot extract min.\n");
        return (pq_node){NULL, 0, 0};
    }
    pq_node min = queue[1];
    queue[1] = queue[*heap_size];
    (*heap_size)--;
    min_heapify(queue, *heap_size, 1);
    return min;
}

void pq_decrease_key(pq_node *queue, size_t i, int key) {
    if(key > queue[i].key) {
        fprintf(stderr, "Error: New key is greater than old key.\n");
        return;
    }
    queue[i].key = key;
    while(i > 1 && queue[i].key < queue[PARENT(i)].key) {
        swap(queue+i, queue+PARENT(i), sizeof(pq_node));
        i = PARENT(i);
    }
}

void pq_insert(pq_node *queue, size_t *heap_size, pq_node node) {
    (*heap_size)++;
    int key = node.key;
    queue[*heap_size] = node;
    queue[*heap_size].key = INT_MAX;
    pq_decrease_key(queue, *heap_size, key);
}

// int main(void) {
//     pq_node arr[] = {{0, NULL}, {5, NULL}, {2, NULL}, {7, NULL}, {3, NULL}, {9, NULL}, {1, NULL}, {8, NULL}, {2, NULL}};
//     size_t heap_size = sizeof(arr)/sizeof(pq_node) - 2;
//     pq_build(arr, heap_size);
//     for(size_t i = 1; i < sizeof(arr)/sizeof(pq_node); i++) {
//         printf("%2d", arr[i].key);
//     }
//     printf("\n");
//     pq_insert(arr, &heap_size, 2);
//     for(size_t i = 1; i < sizeof(arr)/sizeof(pq_node); i++) {
//         printf("%2d", arr[i].key);
//     }
// }