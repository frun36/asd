#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define PARENT(i) (i>>1)
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)
#define TEST printf("%d\n", is_sorted(arr, LENGTH))
#define RANGE 1000000

int *generate_array(int);
void print_array(int[], int);
int is_sorted(int[], int);
static inline void swap(int*, int*);
void safe_free(void**);
void sort_time(void (int[], int), int[], int, char*);
int intcmp(const void *, const void *);

void bubble_sort(int[], int);
void insertion_sort(int[], int);
void merge(int[], int, int, int);
void merge_sort(int[], int, int);
void merge_sort_call(int[], int);
void max_heapify(int[], int, int);
void build_max_heap(int[], int);
void heap_sort(int[], int);
int lpartition(int[], int, int);
void lquicksort(int[], int, int);
void lquicksort_call(int[], int);
int hpartition(int[], int, int);
void hquicksort(int[], int, int);
void hquicksort_call(int[], int);
void qsort_call(int[], int);
void counting_sort(int[], int, int);
void counting_sort_call(int[], int);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if(argc < 2) {
        printf("Array length not specified\n");
        return -1;
    }
    int LENGTH = atoi(argv[1]);
    int *arr_bckp = generate_array(LENGTH);
    int *arr = malloc(LENGTH*sizeof(int));
    
    // arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    // sort_time(bubble_sort, arr, LENGTH, "Bubble sort: ");
    
    // arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    // sort_time(insertion_sort, arr, LENGTH, "Insertion sort: ");
    
    arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    sort_time(heap_sort, arr, LENGTH, "Heap sort: ");
    // printf("%d\n", is_sorted(arr, LENGTH));

    arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    sort_time(merge_sort_call, arr, LENGTH, "Merge sort: ");
    // printf("%d\n", is_sorted(arr, LENGTH));

    arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    sort_time(hquicksort_call, arr, LENGTH, "Quick sort (Hoare): ");
    // printf("%d\n", is_sorted(arr, LENGTH));

    arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    sort_time(lquicksort_call, arr, LENGTH, "Quick sort (Lomuto): ");
    // printf("%d\n", is_sorted(arr, LENGTH));

    arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    sort_time(qsort_call, arr, LENGTH, "stdlib: qsort(): ");
    // TEST;

    arr = memcpy(arr, arr_bckp, LENGTH*sizeof(int));
    sort_time(counting_sort_call, arr, LENGTH, "Counting sort: ");
    // TEST;

    // int array[] = {12, 11, 13, 14};
    // // |  |  |  | {12, 11, 14, 13} | {12, 13, 11, 14} | {12, 13, 14, 11} | {12, 14, 11, 13} | {12, 14, 13, 11} | {13, 11, 12, 14} | {13, 11, 14, 12} | {13, 12, 11, 14} | {13, 12, 14, 11} | {13, 14, 11, 12} | {13, 14, 12, 11} | {14, 11, 12, 13} | {14, 11, 13, 12} | {14, 12, 11, 13} | {14, 12, 13, 11} | {14, 13, 11, 12} | {14, 13, 12, 11}
    // lquicksort_call(array, 4);

    safe_free((void **)&arr_bckp);
    safe_free((void **)&arr);
    return 0;
}

int *generate_array(int len) {
    int *arr = malloc(len*sizeof(int));
    for(int i = 0; i < len; i++) {
        arr[i] = rand() % RANGE;
    }
    return arr;
}

void print_array(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n");
}

int is_sorted(int arr[], int len) {
    for(int i = 1; i < len; i++) {
        if(arr[i - 1] > arr[i]) {
            return 0;
        }
    }
    return 1;
}

static inline void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void safe_free(void **p) {
    if(p && *p) {
        free(*p);
        *p = NULL;
    }
}

void sort_time(void (*sort)(int[], int), int arr[], int len, char *header) {
    clock_t begin = clock();
    sort(arr, len);
    clock_t end = clock();
    printf("%s%fs\n", header, (double)(end - begin) / CLOCKS_PER_SEC);
    return;
}

int intcmp(const void *a, const void *b) {
    return *(int*)a-*(int*)b;
}

void bubble_sort(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        for(int j = 1; j < len - i; j++) {
            if(arr[j-1] > arr[j]) {
                swap(&arr[j-1], &arr[j]);
            }
        }
    }
}

void insertion_sort(int arr[], int len) {
    int key, j;
    for(int i = 1; i < len; i++) {
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void merge(int arr[], int p, int q, int r) {
    int len_1 = q-p+1;
    int len_2 = r-q;
    int *arr_1 = malloc((len_1+1)*sizeof(int));
    int *arr_2 = malloc((len_2+1)*sizeof(int));
    // int arr_1[len_1+1];
    // int arr_2[len_2+1];
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
        if(arr_1[i] < arr_2[j]) {
            arr[k] = arr_1[i];
            i++;
        }
        else {
            arr[k] = arr_2[j];
            j++;
        }
    }
    safe_free((void **)&arr_1);
    safe_free((void **)&arr_2);
}

void merge_sort(int arr[], int p, int q) {
    if(p < q) {
        int mid = (p+q)/2;
        merge_sort(arr, p, mid);
        merge_sort(arr, mid+1, q);
        merge(arr, p, mid, q);
    }
}

void merge_sort_call(int arr[], int len) {
    merge_sort(arr, 0, len-1);
}

void max_heapify(int arr[], int heap_size, int index) {
    int l = LEFT(index);
    int r = RIGHT(index);
    int largest = index;
    while((l <= heap_size && arr[l-1] > arr[index-1]) || (r <= heap_size && arr[r-1] > arr[index-1])) {
        if(l <= heap_size && arr[l-1] > arr[largest-1]) {
            largest = l;
        }
        if(r <= heap_size && arr[r-1] > arr[largest-1]) {
            largest = r;
        }
        if(largest != index) {
            swap(arr+index-1, arr+largest-1);
            index = largest;
        }
        l = LEFT(index);
        r = RIGHT(index);
    }
}

void build_max_heap(int arr[], int len) {
    for(int i = len/2; i >= 1; i--) {
        max_heapify(arr, len, i);
    }
}

void heap_sort(int arr[], int len) {
    int heap_size = len;
    build_max_heap(arr, heap_size);
    for(int i = len-1; i >= 1; i--) {
        swap(arr, arr+i);
        heap_size--;
        max_heapify(arr, heap_size, 1);
    }
}

int lpartition(int arr[], int p, int r) {
    int wall = p-1;
    for(int i = p; i < r; i++) {
        if(arr[i] < arr[r]) {
            wall++;
            swap(arr+i, arr+wall);
        }
    }
    swap(arr+r, arr+wall+1);
    // for(int a = p; a < wall+1; a++) {
    //     printf("%3d", arr[a]);
    // }
    // printf("|%3d|", arr[wall+1]);
    // for(int b = wall+2; b < r+1; b++)
    //     printf("%3d", arr[b]);
    // printf("\n");
    return wall+1;
}

void lquicksort(int arr[], int p, int r) {    
    // while(p < r) {
    if (p < r) {
        int q = lpartition(arr, p, r);
        lquicksort(arr, p, q-1);
        lquicksort(arr, q+1, r);
        p = q+1;
    }
}

void lquicksort_call(int arr[], int len) {
    lquicksort(arr, 0, len-1);
}

int hpartition(int arr[], int p, int r) {
    int pivot = arr[(r-p)/2+p];
    int i = p-1;
    int j = r+1;
    while(1) {
        while(arr[++i] < pivot)
            ;
        while(arr[--j] > pivot)
            ;
        if(i >= j) return j;
        swap(arr+i, arr+j);
    }
}

void hquicksort(int arr[], int p, int r) {    
    if(p < r) {
        int q = hpartition(arr, p, r);
        hquicksort(arr, p, q);
        hquicksort(arr, q+1, r);
    }
}

void hquicksort_call(int arr[], int len) {
    hquicksort(arr, 0, len-1);
}

void qsort_call(int arr[], int len) {
    qsort(arr, len, sizeof(int), intcmp);
}

void counting_sort(int arr[], int len, int range) {
    int *counter = calloc(range, sizeof(int));
    int *bckp = malloc(sizeof(int)*len);
    bckp = memcpy(bckp, arr, len*sizeof(int));
    for(int i = 0; i < len; i++) {
        counter[arr[i]] += 1;
    }
    // print_array(counter, range);
    for(int i = 1; i < range; i++) {
        counter[i] += counter[i-1];
    }
    // print_array(counter, range);
    for(int i = len-1; i >= 0; i--) {
        arr[counter[bckp[i]]-1] = bckp[i];
        // print_array(arr, len);
        counter[bckp[i]] -= 1;
    }
    safe_free((void **)&counter);
    safe_free((void **)&bckp);
}

void counting_sort_call(int arr[], int len) {
    counting_sort(arr, len, RANGE);
}
