#include "list.h"

List list_init() {
    return (List){NULL};
}

Node *list_add_begin(List *list, void *data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    return new_node;
}

Node *list_add_end(List *list, void *data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    Node *cursor = list->head;
    if (cursor == NULL) {
        list->head = new_node;
        return new_node;
    }
    while (cursor->next) {
        cursor = cursor->next;
    }
    cursor->next = new_node;
    return new_node;
}

void list_print(List *list, printData print_data) {
    Node *curr = list->head;
    printf("---HEAD---\n");
    while (curr) {
        printf("Node: %p\n", curr);
        print_data(curr->data);
        printf("Next: %p\n", curr->next);
        printf("-----\n");
        curr = curr->next;
    }
}

void list_clear(List *list, freeData free_data) {
    if (list->head == NULL) {
        return;
    }
    Node *curr = list->head;
    Node *next;
    do {
        next = curr->next;
        list_free_node(curr, free_data);
        curr = next;
    } while (curr);
    list->head = NULL;
}

void list_remove(List *list, Node *curr, freeData free_data) {
    if (list->head == NULL) {
        return;
    }
    if (list->head == curr) {
        list->head = curr->next;
        list_free_node(curr, free_data);
        return;
    }

    Node *prev = list->head;
    while (prev->next != curr) {
        prev = prev->next;
    }
    prev->next = curr->next;
    list_free_node(curr, free_data);
}

void list_free_node(Node *node, freeData free_data) {
    if (free_data) {
        free_data(node->data);
    }
    free(node);
}

Node *list_find(List *list, void *data, cmpData cmp_data) {
    Node *curr = list->head;
    while (curr) {
        if (cmp_data(curr->data, data) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}