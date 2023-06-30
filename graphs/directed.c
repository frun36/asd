#include "directed.h"

// Matrix representation

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

void print_vertex_data(void* v) {
    Vertex* vertex = v;
    if (v) {
        printf("\nIndex: %lu\nColor: %d\nDistance: %u\nd: %u\nf: %d\n", vertex->index, vertex->color, vertex->distance, vertex->d, vertex->f);
    } else {
        printf(".\n");
    }
}

int vertex_cmp(void* a, void* b) {
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

DiGraphList* dgl_init(size_t order) {
    DiGraphList* graph = malloc(sizeof(DiGraphList) + order * order * sizeof(Vertex));
    graph->order = order;
    for (size_t i = 0; i < order; i++) {
        graph->vertices[i].index = i;
        graph->vertices[i].adj = malloc(sizeof(List));
        *graph->vertices[i].adj = list_init();
    }
    return graph;
}

void dgl_add_edge(DiGraphList* graph, size_t u, size_t v) {
    if (u >= graph->order) {
        fprintf(stderr, "Couldn't add edge (%lu, %lu): vertex %lu not in graph\n", u, v, u);
        return;
    }
    if (v >= graph->order) {
        fprintf(stderr, "Couldn't add edge (%lu, %lu): vertex %lu not in graph\n", u, v, v);
        return;
    }
    if (list_find(graph->vertices[u].adj, &graph->vertices[v], vertex_cmp)) {
        fprintf(stderr, "Couldn't add edge (%lu, %lu): edge already exists\n", u, v);
        return;
    }
    list_add_end(graph->vertices[u].adj, &graph->vertices[v]);
    printf("Successfully added edge (%lu, %lu)\n", u, v);
}

void dgl_remove_edge(DiGraphList* graph, size_t u, size_t v) {
    if (u >= graph->order) {
        fprintf(stderr, "Couldn't remove edge (%lu, %lu): vertex %lu not in graph\n", u, v, u);
        return;
    }
    if (v >= graph->order) {
        fprintf(stderr, "Couldn't remove edge (%lu, %lu): vertex %lu not in graph\n", u, v, v);
        return;
    }
    Node* edge = list_find(graph->vertices[u].adj, &graph->vertices[v], vertex_cmp);
    if (!edge) {
        fprintf(stderr, "Couldn't remove edge (%lu, %lu): edge doesn't exist\n", u, v);
        return;
    }
    list_remove(graph->vertices[u].adj, edge, NULL);
    printf("Successfully removed edge (%lu, %lu)\n", u, v);
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
            printf("%3d", list_find(graph->vertices[i].adj, &graph->vertices[j], vertex_cmp) ? 1 : 0);
        }
        printf("\n");
    }
}

void dgl_free(DiGraphList** graph) {
    if (graph && *graph) {
        for (size_t i = 0; i < (*graph)->order; i++) {
            list_clear((*graph)->vertices[i].adj, NULL);
            free((*graph)->vertices[i].adj);
        }
        free(*graph);
    }
    *graph = NULL;
}

void bfs(DiGraphList* graph, size_t source) {
    size_t indices[graph->order];
    for (size_t i = 0; i < graph->order; i++) {
        if (i != source) {
            graph->vertices[i].color = WHITE;
            graph->vertices[i].distance = -1;  // overflow on purpose
            graph->vertices[i].predecessor = NULL;
        }
        indices[i] = i;
    }
    graph->vertices[source].color = GRAY;
    graph->vertices[source].distance = 0;
    graph->vertices[source].predecessor = NULL;

    Fifo* fifo = fifo_init(graph->order - 1);
    fifo_enqueue(fifo, indices + source);
    while (fifo->queue[fifo->begin]) {
        fifo_print(fifo, print_vertex_data);
        size_t curr_index = *(size_t*)fifo_dequeue(fifo);
        Vertex* curr = &graph->vertices[curr_index];
        Node* neighbor = curr->adj->head;
        while (neighbor) {
            Vertex* neighbor_vertex = neighbor->data;
            if (neighbor_vertex->color == WHITE) {
                neighbor_vertex->color = GRAY;
                neighbor_vertex->distance = curr->distance + 1;
                neighbor_vertex->predecessor = curr;
                fifo_enqueue(fifo, neighbor_vertex);
            }
            neighbor = neighbor->next;
        }
        curr->color = BLACK;
        printf("Visited vertex %lu\n", curr_index);
    }

    // test
    printf("\nFinished\n");
    for (size_t i = 0; i < graph->order; i++) {
        print_vertex_data(&graph->vertices[i]);
    }
}

void dfs(DiGraphList* graph) {
    for (size_t i = 0; i < graph->order; i++) {
        graph->vertices[i].color = WHITE;
        graph->vertices[i].predecessor = NULL;
    }
    unsigned time = 0;
    for (size_t i = 0; i < graph->order; i++) {
        if (graph->vertices[i].color == WHITE) {
            dfs_visit(&graph->vertices[i], &time);
        }
    }

    // test
    printf("\nFinished\n");
    for (size_t i = 0; i < graph->order; i++) {
        print_vertex_data(&graph->vertices[i]);
    }
}

void dfs_visit(Vertex* curr, unsigned* time) {
    curr->color = GRAY;
    ++*time;
    curr->d = *time;
    Node* neighbor = curr->adj->head;
    while (neighbor) {
        Vertex* neighbor_vertex = neighbor->data;
        if (neighbor_vertex->color == WHITE) {
            neighbor_vertex->predecessor = curr;
            dfs_visit(neighbor_vertex, time);
        }
        neighbor = neighbor->next;
    }
    curr->color = BLACK;
    ++*time;
    curr->f = *time;
}