#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

#define CHAR_AMOUNT 128

typedef struct tsymbol {
    unsigned char position;
    unsigned value;
} symbol;

pq_node *initialize_queue(size_t len);
void count_chars(FILE* file, pq_node* queue);
void print_queue(pq_node* queue, size_t len);
void free_all(pq_node* queue, size_t len);
void huffman_make_tree(pq_node* queue, size_t heap_size);
void huffman_read_tree(symbol* codes, char* first, char* last);
void append_bit(symbol *s, unsigned char bit);
void print_binary(symbol *s);

int main(void) {
    FILE *file = fopen("macbeth.txt", "r");
    if(!file) {
        fprintf(stderr, "Error: Can't open file.\n");
        return 1;
    }

    pq_node *queue = initialize_queue(CHAR_AMOUNT);
    count_chars(file, queue);

    fclose(file);

    // char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    // pq_node arr[] = {{NULL, 0, 0}, {&a, 1, 7}, {&b, 1, 2}, {&c, 1, 3}, {&d, 1, 5}, {&e, 1, 0}};
    // pq_build(arr, 5);
    // print_queue(arr, 5);

    pq_build(queue, CHAR_AMOUNT);
    // print_queue(queue, CHAR_AMOUNT);
    huffman_make_tree(queue, CHAR_AMOUNT);
    symbol codes[CHAR_AMOUNT];
    for(size_t i = 0; i < CHAR_AMOUNT; i++) {
        codes[i].position = codes[i].value = 0;
    }

    // symbol s = {0, 0};
    // append_bit(&s, 1);
    // append_bit(&s, 0);
    // append_bit(&s, 1);
    // printf("%d", s.value);

    for(size_t i = 0; i < 2*CHAR_AMOUNT-1; i++) {
        if(i % 2 == 0) {
            // printf("'%c' (%d)\n", *((char *)queue[1].data + i), *((char *)queue[1].data + i));
            printf("(%d)\n", *((char *)queue[1].data + i));
        }
        else {
            printf("%d ", *((char *)queue[1].data + i));
        }
    }

    huffman_read_tree(codes, queue[1].data, queue[1].data + queue[1].data_size);

    // char carr[] = {0, -5, 2, -2, 1, -4, 5, -1, 4, -3, 3};
    // symbol sarr[6] = {};
    // for(size_t i = 0; i < 11; i++) {
    //     sarr[i].position = sarr[i].value = 0;
    // }
    // huffman_read_tree(sarr, carr, carr+11);
    // for(size_t i = 0; i < 6; i++) {
    //     print_binary(sarr+i);
    // }
    // printf("---\n");

    // char carr[] = {0, -1, 1};
    // symbol sarr[2];
    // for(size_t i = 0; i < 2; i++) {
    //     sarr[i].position = sarr[i].value = 0;
    // }
    // huffman_read_tree(sarr, carr, carr+3);
    // for(size_t i = 0; i < 2; i++) {
    //     print_binary(sarr+i);
    // }

    for(size_t i = 0; i < CHAR_AMOUNT; i++) {
        // printf("%d %d\n", codes[i].position, codes[i].value);
        print_binary(codes+i);
    }

    // symbol s = {8, 0xba};
    // print_binary(&s);

    // print_queue(queue, 1);
    return 0;
}

pq_node *initialize_queue(size_t len) {
    pq_node *queue = pq_allocate(len);
    char *tmp = 0;
    for(size_t i = 1; i <= len; i++) {
        queue[i].data_size = 1;
        tmp = malloc(1);
        *tmp = (char)i - 1;
        queue[i].data = (void *)tmp;
    }
    return queue;
}

void print_queue(pq_node* queue, size_t len) {
    for(size_t i = 1; i <= len; i++) {
        // printf("Index: %ld\nKey: %d\nData: %d (%c)\n\n", i, queue[i].key, *((char*)queue[i].data), *((char*)queue[i].data));
        printf("Index: %ld\nKey: %d\nData: ", i, queue[i].key);
        for(size_t j = 0; j < queue[i].data_size; j++) {
            printf("%8d", ((char*)queue[i].data)[j]);
        }
        printf("\t");
        for(size_t j = 0; j < queue[i].data_size; j++) {
            printf("'%c', ", ((char*)queue[i].data)[j]);
        }
        printf("\n");
    }
}

void count_chars(FILE* file, pq_node* queue) {
    char c = 0;
    while((c = fgetc(file)) != EOF) {
        queue[(size_t)c + 1].key++;
    }
}

void free_all(pq_node* queue, size_t len) {
    for(size_t i = 1; i <= len; i++) {
        free(queue[i].data);
    }
    free(queue);
}

void huffman_make_tree(pq_node* queue, size_t heap_size) {
    char count = 0;
    char *new_data;
    size_t new_size;
    while(heap_size > 1) {
        count--;
        pq_node a = pq_extract_min(queue, &heap_size);
        pq_node b = pq_extract_min(queue, &heap_size);
        new_size = a.data_size + b.data_size + 1;
        new_data = malloc(new_size);
        memcpy(new_data, a.data, a.data_size);
        new_data[a.data_size] = count;
        free(a.data);
        a.data = NULL;
        memcpy(new_data + a.data_size + 1, b.data, b.data_size);
        free(b.data);
        b.data = NULL;
        pq_insert(queue, &heap_size, (pq_node){(void *)new_data, new_size, a.key + b.key});
    }
}

// void huffman_read_tree(symbol* codes, char* tree, size_t length) {
//     int side = 0;
//     for(char count = -127; count < 0; count++) {
//         for(size_t i = 0; i < length; i++) {
//             if(tree[i] == count) {
//                 side = 1;
//             }
//             if(tree[i] >= 0) {
//                 append_bit(codes + tree[i], side);
//             }
//         }
//         side = 0;
//     }
// }


void huffman_read_tree(symbol* codes, char* first, char* last) {
    char* min = first;
    for(size_t i = 1; i < (size_t)(last-first); i += 2) {
        if(first[i] < *min) {
            min = first+i;
        }
    }
    // if(*min >= 0) {
    //     return;
    // }

    for(size_t i = 0; i < (size_t)(min-first); i += 2) {
        if(first[i] >= 0) {
            append_bit(codes + first[i], 0);
        }
    }
    for(size_t i = 1; i < (size_t)(last-min); i += 2) {
        if(min[i] >= 0) {
            append_bit(codes + min[i], 1);
        }
    }
    if(min != first) {
        huffman_read_tree(codes, first, min);
        huffman_read_tree(codes, min + 1, last);
    }
}

void append_bit(symbol *s, unsigned char bit) {
    s->position++;
    if(bit) {
        s->value |= (1 << (8*sizeof(s->value) - s->position));
    }
    else {
        s->value &= ~(1 << (8*sizeof(s->value) - s->position));
    }
}

void print_binary(symbol *s) {
    printf("%d\t%u\t", s->position, s->value);
    for(size_t i = 0; i < s->position; i++) {
        printf("%d", (s->value >> (8*sizeof(s->value) - i - 1)) & 1);
    }
    putchar('\n');
}