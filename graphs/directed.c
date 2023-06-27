#include "directed.h"


//Matrix representation

DiGraphMatrix* dgm_init(size_t order) {
    DiGraphMatrix* graph = calloc(
        sizeof(DiGraphMatrix) + order * order * sizeof(int), sizeof(int));
    graph->order = order;
    return graph;
}

void dgm_add_edge(DiGraphMatrix* graph, size_t u, size_t v) {
    if (u >= graph->order) {
        fprintf(stderr, "Couldn't add edge: vertex %lu not in graph\n", u);
        return;
    }
    if (v >= graph->order) {
        fprintf(stderr, "Couldn't add edge: vertex %lu not in graph\n", v);
        return;
    }
    size_t i = get_index(graph->order, u, v);
    if (graph->edges[i] == 1) {
        fprintf(stderr, "Couldn't add edge: edge already exists\n");
        return;
    }
    graph->edges[i] = 1;
    printf("Successfully added edge: (%lu, %lu)\n", u, v);
}

void dgm_remove_edge(DiGraphMatrix* graph, size_t u, size_t v) {
    if (u >= graph->order) {
        fprintf(stderr, "Couldn't add edge: vertex %lu not in graph\n", u);
        return;
    }
    if (v >= graph->order) {
        fprintf(stderr, "Couldn't add edge: vertex %lu not in graph\n", v);
        return;
    }
    size_t i = get_index(graph->order, u, v);
    if (graph->edges[i] == 0) {
        fprintf(stderr, "Couldn't remove edge: edge doesn't exist\n");
        return;
    }
    graph->edges[i] = 0;
    printf("Successfully removed edge: (%lu, %lu)\n", u, v);
}

void dgm_print(DiGraphMatrix* graph) {
    printf("   ");
    for (size_t i = 0; i < graph->order; i++) {
        printf("%3lu", i);
    }
    printf("\n");
    for (size_t i = 0; i < graph->order; i++) {
        printf("%3lu", i);
        for (size_t j = 0; j < graph->order; j++) {
            printf("%3d", graph->edges[get_index(graph->order, i, j)]);
        }
        printf("\n");
    }
}

void dgm_free(DiGraphMatrix** graph) {
    if (graph && *graph) {
        free(*graph);
    }
    *graph = NULL;
}

// List representation

void print_size_t_data(void* data) {
    printf("Data: %lu\n", *(size_t*)data);
}

int size_t_cmp(void* _a, void* _b) {
    size_t a = *(size_t*)_a;
    size_t b = *(size_t*)_b;
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

DiGraphList* dgl_init(size_t order) {
    DiGraphList* graph = malloc(sizeof(DiGraphMatrix) + order * order * sizeof(List));
    graph->order = order;
    for (size_t i = 0; i < order; i++) {
        graph->adj[i] = list_init();
    }
    return graph;
}

void dgl_add_edge(DiGraphList* graph, size_t u, size_t v) {
    if (u >= graph->order) {
        fprintf(stderr, "Couldn't add edge: vertex %lu not in graph\n", u);
        return;
    }
    if (v >= graph->order) {
        fprintf(stderr, "Couldn't add edge: vertex %lu not in graph\n", v);
        return;
    }
    if (list_find(&graph->adj[u], &v, size_t_cmp)) {
        fprintf(stderr, "Couldn't add edge: edge already exists\n");
        return;
    }
    size_t* data = malloc(sizeof(size_t));
    *data = v;
    list_add_end(&graph->adj[u], data);
    printf("Successfully added edge: (%lu, %lu)\n", u, v);
}

void dgl_remove_edge(DiGraphList* graph, size_t u, size_t v) {
    if (u >= graph->order) {
        fprintf(stderr, "Couldn't remove edge: vertex %lu not in graph\n", u);
        return;
    }
    if (v >= graph->order) {
        fprintf(stderr, "Couldn't remove edge: vertex %lu not in graph\n", v);
        return;
    }
    Node* edge = list_find(&graph->adj[u], &v, size_t_cmp);
    if (!edge) {
        fprintf(stderr, "Couldn't remove edge: edge doesn't exist\n");
        return;
    }
    list_remove(&graph->adj[u], edge, free);
    printf("Successfully removed edge: (%lu, %lu)\n", u, v);
}

void dgl_print(DiGraphList* graph) {
    printf("   ");
    for (size_t i = 0; i < graph->order; i++) {
        printf("%3lu", i);
    }
    printf("\n");
    for (size_t i = 0; i < graph->order; i++) {
        printf("%3lu", i);
        for (size_t j = 0; j < graph->order; j++) {
            printf("%3d", list_find(&graph->adj[i], &j, size_t_cmp) ? 1 : 0);
        }
        printf("\n");
    }
}

void dgl_free(DiGraphList** graph) {
    if (graph && *graph) {
        for (size_t i = 0; i < (*graph)->order; i++) {
            list_clear(&(*graph)->adj[i], free);
        }
        free(*graph);
    }
    *graph = NULL;
}