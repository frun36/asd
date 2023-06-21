#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define free_tree(tree) { \
    free_branch(tree.root); \
    tree.root = NULL; \
}

#define preorder_print(tree) {\
    preorder_tree_walk(tree.root); \
    printf("\n"); \
}

#define inorder_print(tree) {\
    inorder_tree_walk(tree.root); \
    printf("\n"); \
}

#define postorder_print(tree) {\
    postorder_tree_walk(tree.root); \
    printf("\n"); \
}

#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))


typedef struct _Node {
    int key;
    struct _Node* parent;
    struct _Node* left;
    struct _Node* right;
} Node;

typedef struct _Tree {
    Node* root;
} Tree;

Tree new_tree();
Tree example(void);
void preorder_tree_walk(Node*);
void inorder_tree_walk(Node*);
void postorder_tree_walk(Node*);
void tree_transplant(Tree*, Node*, Node*);
void free_branch(Node*);
