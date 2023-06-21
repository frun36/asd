#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Node *bst_search(Node*, int);
Node *bst_minimum(Node*);
Node *bst_maximum(Node*);
Node *bst_successor(Node*);
Node *bst_predecessor(Node*);
void bst_insert(Tree*, int);
void bst_delete(Tree*, Node*);
int is_bst(Node*, int, int);

int main(void) {
    // Tree tree = example();
    Tree tree = new_tree();
    bst_insert(&tree, 6);
    bst_insert(&tree, 5);
    bst_insert(&tree, 2);
    bst_insert(&tree, 5);
    bst_insert(&tree, 7);
    bst_insert(&tree, 8);
    inorder_print(tree);
    printf("%d\n", is_bst(tree.root, 0, 100));
    bst_delete(&tree, tree.root->right);
    inorder_print(tree);
    printf("%d\n", is_bst(tree.root, 0, 100));

    // Node *predecessor = bst_predecessor(tree.root->left->left);
    // Node *successor = bst_successor(tree.root->left->left);

    // printf("%3d%3d%3d\n", predecessor ? predecessor->key : -1, tree.root->left->left->key, successor ? successor->key : -1); 
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

void bst_insert(Tree* tree, int key) {
    Node *x = tree->root;

    Node *z = malloc(sizeof(Node));
    z->key = key;
    z->parent = NULL;
    z->left = NULL;
    z->right = NULL;

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
}

void bst_delete(Tree* tree, Node* z) {
    if(z->left == NULL) {
        tree_transplant(tree, z, z->right);
    }
    else if(z->right == NULL) {
        tree_transplant(tree, z, z->left);
    }
    else {
        Node *y = bst_minimum(z);
        if(y->parent != z) {
            y->parent->left = y->right;
            y->right->parent = y->parent;
            y->right = z->right;
        }
        z->right = NULL;
        y->left = z->left;
        z->left = NULL;
        tree_transplant(tree, z, y);
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