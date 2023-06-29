#ifndef DIRECTED_H
#define DIRECTED_H

#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"
#include "list.h"

#define get_index(order, u, v) ((u) * (order) + (v))

// Matrix representation

typedef struct _DiGraphMatrix {
    size_t order;
    int edges[];
} DiGraphMatrix;

DiGraphMatrix *dgm_init(size_t);
void dgm_add_edge(DiGraphMatrix *, size_t, size_t);
void dgm_remove_edge(DiGraphMatrix *, size_t, size_t);
void dgm_print(DiGraphMatrix *);
void dgm_free(DiGraphMatrix **);

// List representation

enum Color { BLACK,
             GRAY,
             WHITE };

typedef struct _Vertex {
    size_t index;
    enum Color color;
    struct _Vertex *predecessor;
    unsigned distance;
    unsigned d;
    unsigned f;
    List *adj;
} Vertex;

typedef struct _DiGraphList {
    size_t order;
    Vertex vertices[];
} DiGraphList;

DiGraphList *dgl_init(size_t);
void print_vertex_data(void *);
int vertex_cmp(void *, void *);
void dgl_add_edge(DiGraphList *, size_t, size_t);
void dgl_remove_edge(DiGraphList *, size_t, size_t);
void dgl_print(DiGraphList *);
void bfs(DiGraphList *, size_t);
void dgl_free(DiGraphList **);

#endif