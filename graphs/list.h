#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    void *data;
    struct _Node *next;
} Node;

typedef struct _List {
    Node *head;
} List;

typedef void (*printData)(void *);
typedef void (*freeData)(void *);
typedef int (*cmpData)(void *, void *);

List list_init();
Node *list_add_begin(List *, void *);
Node *list_add_end(List *, void *);
void list_print(List *, printData);
void list_remove(List *, Node *, freeData);
void list_clear(List *, freeData);
void list_free_node(Node *, freeData);
Node *list_find(List *, void *, cmpData);

#endif