#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./pascal <height>\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int p[n+1][n+1];
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            if(k == 0) {
                p[i][k] = 1;
            } else if(k > i) {
                p[i][k] = 0;
            } else {
                p[i][k] = p[i-1][k-1] + p[i-1][k];
            }
            // printf("%8d", p[i][k]);
        }
        // printf("\n");
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            printf("%8d", p[i][j]);
        }
        printf("\n");
    }
}