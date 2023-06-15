#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#define LENGTH 100
#define PAIRS (LENGTH*(LENGTH-1)/2)

/**
 * @brief Generates array of given length
 * @param int[] target array
 * @param int target array length
*/
void generate_array(int[], int);
int merge(int[], int, int, int);
int merge_sort(int[], int, int);
void print_array(int[], int);

int main(void) {
    srand(time(NULL));
    int arr[LENGTH];
    for(int i = 0; i < 1000; i++) {
        generate_array(arr, LENGTH);
        printf("%f\n", (double)merge_sort(arr, 0, LENGTH-1)/PAIRS);
    }
    return 0;
}

int merge(int arr[], int p, int q, int r) {
    int inv = 0;
    int len_1 = q-p+1;
    int len_2 = r-q;
    int arr_1[len_1+1];
    int arr_2[len_2+1];
    for(int i = 0; i < len_1; i++) {
        arr_1[i] = arr[p+i];
    }
    for(int i = 0; i < len_2; i++) {
        arr_2[i] = arr[q+i+1];
    }
    arr_1[len_1] = INT_MAX;
    arr_2[len_2] = INT_MAX;

    int i = 0, j = 0;

    for(int k = p; k < r + 1; k++) {
        if(arr_1[i] <= arr_2[j]) {
            arr[k] = arr_1[i];
            i++;
        }
        else {
            arr[k] = arr_2[j];
            j++;
            inv += len_1-i;
        }
    }
    return inv;
}

int merge_sort(int arr[], int p, int q) {
    int inv = 0;
    if(p < q) {
        int mid = (p+q)/2;
        inv = merge_sort(arr, p, mid);
        inv += merge_sort(arr, mid+1, q);
        inv += merge(arr, p, mid, q);
    }
    return inv;
}

void print_array(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n");
}

void generate_array(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        arr[i] = rand() % 1000;
    }
}