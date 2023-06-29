#include "directed.h"
#include "list.h"

void print_int(void *i) {
    if (i) {
        printf("%d\n", *(int *)i);
    } else {
        printf(".\n");
    }
}

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
    // {
    //     DiGraphMatrix *graph = dgm_init(5);
    //     dgm_print(graph);
    //     dgm_add_edge(graph, 1, 2);
    //     dgm_print(graph);
    //     dgm_add_edge(graph, 1, 2);
    //     dgm_print(graph);
    //     dgm_add_edge(graph, 1, 1);
    //     dgm_print(graph);
    //     dgm_add_edge(graph, 12, 2);
    //     dgm_print(graph);
    //     dgm_remove_edge(graph, 1, 2);
    //     dgm_print(graph);
    //     dgm_free(&graph);
    // }
    // printf("---------------\n");
    {
        // DiGraphList *graph = dgl_init(5);
        // dgl_print(graph);
        // dgl_add_edge(graph, 1, 2);
        // dgl_print(graph);
        // dgl_add_edge(graph, 1, 2);
        // dgl_print(graph);
        // dgl_add_edge(graph, 1, 1);
        // dgl_print(graph);
        // dgl_add_edge(graph, 12, 2);
        // dgl_print(graph);
        // dgl_remove_edge(graph, 1, 2);
        // dgl_print(graph);

        DiGraphList *graph = dgl_init(8);
        // dgl_add_edge(graph, 0, 1);
        // dgl_add_edge(graph, 0, 4);
        // dgl_add_edge(graph, 1, 5);
        // dgl_add_edge(graph, 5, 2);
        // dgl_add_edge(graph, 5, 6);
        // dgl_add_edge(graph, 2, 3);
        // dgl_add_edge(graph, 6, 7);
        dgl_add_edge(graph, 0, 1);
        dgl_add_edge(graph, 0, 2);
        dgl_add_edge(graph, 0, 3);
        dgl_add_edge(graph, 0, 4);
        dgl_add_edge(graph, 0, 5);
        dgl_add_edge(graph, 0, 6);
        dgl_add_edge(graph, 0, 7);
        
        dgl_print(graph);

        bfs(graph, 0);
        dgl_free(&graph);
    }

    // Fifo *fifo = fifo_init(3);
    // fifo_print(fifo, print_int);
    // fifo_enqueue(fifo, keys);
    // fifo_print(fifo, print_int);
    // fifo_enqueue(fifo, keys + 1);
    // fifo_print(fifo, print_int);
    // fifo_enqueue(fifo, keys + 2);
    // fifo_print(fifo, print_int);
    // fifo_dequeue(fifo);
    // fifo_print(fifo, print_int);
    // fifo_enqueue(fifo, keys);
    // fifo_print(fifo, print_int);
    // fifo_enqueue(fifo, keys);
    // fifo_print(fifo, print_int);
    // printf("%d\n", *(int*)fifo_dequeue(fifo));
    // fifo_print(fifo, print_int);
    // fifo_dequeue(fifo);
    // fifo_print(fifo, print_int);
    // // fifo_dequeue(fifo);
    // // fifo_print(fifo, print_int);
    // fifo_enqueue(fifo, keys);
    // fifo_print(fifo, print_int);
    // fifo_free(&fifo, NULL);
    return 0;
}