#include <stdio.h>
#define PRINT(int) printf("%d\n", int)

void swap_add(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap_xor(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main(void) {
    int a = 115, b = 7;
    swap_xor(&a, &b);
    PRINT(a); PRINT(b);
}