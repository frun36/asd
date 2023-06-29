#include "directed.h"
#include "priority_queue.h"


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

void print_vertex_data(void* data) {
    printf("Data: %p\n", data);
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

// void bfs(DiGraphList *graph, size_t source) {
//     for(size_t i = 0; i < graph->order; i++) {
//         if(i != source) {
//             graph->vertices[i].color = WHITE;
//             graph->vertices[i].predecessor = 
//         }
//     }
// }