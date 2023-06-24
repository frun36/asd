#include "tree.h"

Tree new_tree() {
    return (Tree){NULL};
}

void free_branch(Node* x) {
    if(x) {
        printf("%p %d %p %p\n", x->parent, x->key, x->left, x->right);
        if(x->parent) {
            if(x == x->parent->left) {
                x->parent->left = NULL;
            }
            else {
                x->parent->right = NULL;
            }
        }
        free_branch(x->left);
        free_branch(x->right);
        free(x);
    }
}

void preorder_tree_walk(Node* x) {
    if(x) {
        rb_color(x);
        printf("%3d", x->key);
        preorder_tree_walk(x->left);
        preorder_tree_walk(x->right);
    } else {
        color_black;
        printf("  -");
    }
}

void inorder_tree_walk(Node* x) {
    if(x) {
        inorder_tree_walk(x->left);
        rb_color(x);
        printf("%3d", x->key);
        inorder_tree_walk(x->right);
    }
}

void postorder_tree_walk(Node* x) {
    if(x) {
        postorder_tree_walk(x->left);
        postorder_tree_walk(x->right);
        rb_color(x);
        printf("%3d", x->key);
    }
}

void tree_transplant(Tree* tree, Node* dest, Node* src) {
    if(dest->parent == NULL) {
        tree->root = src;
    }
    else if(dest == dest->parent->left) {
        dest->parent->left = src;
    }
    else {
        dest->parent->right = src;
    }
    if(src) {
        src->parent = dest->parent;
    }
}

Tree example(void) {
    Node* a = malloc(sizeof(Node));
    Node* b = malloc(sizeof(Node));
    Node* c = malloc(sizeof(Node));
    Node* d = malloc(sizeof(Node));
    Node* e = malloc(sizeof(Node));
    Node* f = malloc(sizeof(Node));
    a->key = 6;
    a->parent = NULL;
    a->left = b;
    a->right = c;
    
    b->key = 5;
    b->parent = a;
    b->left = d;
    b->right = e;
    
    c->key = 7;
    c->parent = a;
    c->left = NULL;
    c->right = f;

    d->key = 2;
    d->parent = b;
    d->left = NULL;
    d->right = NULL;

    e->key = 5;
    e->parent = b;
    e->left = NULL;
    e->right = NULL;

    f->key = 8;
    f->parent = c;
    f->left = NULL;
    f->right = NULL;

    return (Tree){a};
}
