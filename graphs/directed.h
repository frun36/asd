#ifndef DIRECTED_H
#define DIRECTED_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define get_index(order, u, v) ((u) * (order) + (v))

typedef struct _DiGraphMatrix {
    size_t order;
    int edges[];
} DiGraphMatrix;

DiGraphMatrix *dgm_init(size_t);
void dgm_add_edge(DiGraphMatrix *, size_t, size_t);
void dgm_remove_edge(DiGraphMatrix *, size_t, size_t);
void dgm_print(DiGraphMatrix *);
void dgm_free(DiGraphMatrix **);

typedef struct _DiGraphList {
    size_t order;
    List adj[];
} DiGraphList;

DiGraphList *dgl_init(size_t);

void print_size_t_data(void *);
int size_t_cmp(void *, void *);
void dgl_add_edge(DiGraphList *, size_t, size_t);
void dgl_remove_edge(DiGraphList *, size_t, size_t);
void dgl_print(DiGraphList *);
void dgl_free(DiGraphList **);

#endif