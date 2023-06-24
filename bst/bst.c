#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Node *bst_search(Node*, int);
Node *bst_minimum(Node*);
Node *bst_maximum(Node*);
Node *bst_successor(Node*);
Node *bst_predecessor(Node*);
Node *bst_insert(Tree*, int);
void bst_delete(Tree*, Node*);
int is_bst(Node*, int, int);
void left_rotate(Tree*, Node*);
void right_rotate(Tree*, Node*);
void rb_insert(Tree*, int);
void rb_insert_fixup(Tree*, Node*);

int main(void) {
    // Tree tree = example();
    Tree tree = new_tree();
    int keys[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    for(size_t i = 0; i < sizeof(keys)/sizeof(int); i++) {
        rb_insert(&tree, keys[i]);
        printf("Allocated node %lu\n", i);
    }

    // bst_insert(&tree, 6);
    // bst_insert(&tree, 5);
    // bst_insert(&tree, 2);
    // bst_insert(&tree, 5);
    // bst_insert(&tree, 7);
    // bst_insert(&tree, 8);
    preorder_print(tree);
    printf("%d\n", is_bst(tree.root, 0, 100));

    bst_delete(&tree, tree.root->right->right);
    preorder_print(tree);
    printf("%d\n", is_bst(tree.root, 0, 100));
    
    right_rotate(&tree, tree.root->left);
    preorder_print(tree);
    printf("%d\n", is_bst(tree.root, 0, 100));

    left_rotate(&tree, tree.root->left);
    preorder_print(tree);
    printf("%d\n", is_bst(tree.root, 0, 100));

    free_tree(tree);

    return 0;
}

Node *bst_search(Node* x, int key) {
    while(x && x->key != key) {
        if(key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

Node *bst_minimum(Node* x) {
    while(x->left) {
        x = x->left;
    }
    return x;
}

Node *bst_maximum(Node* x) {
    while(x->right) {
        x = x->right;
    }
    return x;
}

Node *bst_successor(Node* x) {
    if(x->right) {
        return bst_minimum(x->right);
    }
    Node *y = x->parent;
    while(y && x == y->right) {
        x = y;
        y = x->parent;
    }
    return y;
}

Node *bst_predecessor(Node* x) {
    if(x->left) {
        return bst_maximum(x->left);
    }
    Node *y = x->parent;
    while(y && x == y->left) {
        x = y;
        y = x->parent;
    }
    return y;
}

Node *bst_insert(Tree* tree, int key) {
    Node *x = tree->root;

    Node *z = malloc(sizeof(Node));
    z->key = key;
    z->parent = NULL;
    z->left = NULL;
    z->right = NULL;
    z->color = BLACK;

    Node* y = NULL;
    while(x) {
        y = x;
        if(z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL) {
        tree->root = z;
    }
    else {
        if(z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
    }
    return z;
}

void bst_delete(Tree* tree, Node* z) {
    if(z == NULL) {
        return;
    }
    if(z->left == NULL) {
        tree_transplant(tree, z, z->right);
        z->right = NULL;
        free(z);
    }
    else if(z->right == NULL) {
        tree_transplant(tree, z, z->left);
        free(z);
    }
    else {
        Node *y = bst_minimum(z->right);
        if(y->parent != z) {
            tree_transplant(tree, y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
        z->right = NULL;
        y->left = z->left;
        z->left->parent = y;
        z->left = NULL;
        tree_transplant(tree, z, y);
        free(z);
    }
}

int is_bst(Node* x, int min, int max) {
    if((x->left && x->left->key > x->key) || (x->right && x->right->key < x->key)) {
        return 0;
    }

    int a = 1, b = 1;
    if(x->left) {
        a = is_bst(x->left, min, MIN(x->key, max));
    }
    if(x->right) {
        b = is_bst(x->right, MAX(x->key, min), max);
    }
    return a && b;
}

void left_rotate(Tree* tree, Node* x) {
    Node *y = x->right;
    if(y == NULL) {
        fprintf(stderr, "Couldn't perform rotation: right child of x is NULL.\n");
        return;
    }
    
    y->parent = x->parent;
    if(x->parent == NULL) {
        tree->root = y;
    }
    else if(x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    
    x->right = y->left;
    if(x->right) {
        x->right->parent = x;
    }

    y->left = x;
    x->parent = y;
}

void right_rotate(Tree* tree, Node* x) {
    Node *y = x->left;
    if(y == NULL) {
        fprintf(stderr, "Couldn't perform rotation: left child of x is NULL.\n");
        return;
    }

    y->parent = x->parent;
    if(x->parent == NULL) {
        tree->root = y;
    }
    else if(x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    x->left = y->right;
    if(x->left) {
        x->left->parent = x;
    }

    y->right = x;
    x->parent = y;
}

void rb_insert(Tree* tree, int key) {
    Node *z = bst_insert(tree, key);
    z->color = RED;
    rb_insert_fixup(tree, z);
}

void rb_insert_fixup(Tree* tree, Node* z) {
    Node *y;
    while(z->parent && z->parent->color == RED) {
        if(z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if(y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if(y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}
