#include "directed.h"
#include "list.h"

int main(void) {
    // List list = list_init();
    // int keys[] = {1, 2, 3, 4};
    // list_print(&list, print_int_data);
    // list_add_begin(&list, keys + 1);
    // list_print(&list, print_int_data);
    // list_add_end(&list, keys + 2);
    // list_print(&list, print_int_data);
    // list_add_begin(&list, keys);
    // list_print(&list, print_int_data);
    // list_add_end(&list, keys + 3);
    // list_print(&list, print_int_data);
    // list_remove(&list, list.head->next, NULL);
    // list_print(&list, print_int_data);
    // list_clear(&list, NULL);
    // list_print(&list, print_int_data);
    {
        DiGraphMatrix *graph = dgm_init(5);
        dgm_print(graph);
        dgm_add_edge(graph, 1, 2);
        dgm_print(graph);
        dgm_add_edge(graph, 1, 2);
        dgm_print(graph);
        dgm_add_edge(graph, 1, 1);
        dgm_print(graph);
        dgm_add_edge(graph, 12, 2);
        dgm_print(graph);
        dgm_remove_edge(graph, 1, 2);
        dgm_print(graph);
        dgm_free(&graph);
    }
    printf("---------------\n");
    {
        DiGraphList *graph = dgl_init(5);
        dgl_print(graph);
        dgl_add_edge(graph, 1, 2);
        dgl_print(graph);
        dgl_add_edge(graph, 1, 2);
        dgl_print(graph);
        dgl_add_edge(graph, 1, 1);
        dgl_print(graph);
        dgl_add_edge(graph, 12, 2);
        dgl_print(graph);
        dgl_remove_edge(graph, 1, 2);
        dgl_print(graph);
        dgl_free(&graph);
    }
    return 0;
}

void print_int_data(void *data) {
    printf("Data: %d\n", *(int *)data);
}

int int_cmp(void *_a, void *_b) {
    int a = *(int *)_a;
    int b = *(int *)_b;
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}