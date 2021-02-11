#include "array.h"
#include <stdio.h>

double** hilbert_matrix(int n) {
    double** x;
    make_matrix(x, n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x[i][j] = 1.0 / (1 + i + j);
        }
    }

    return x;
}

int main() {
    double** H;
    int n = 8;
    H = hilbert_matrix(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", H[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n");
    print_matrix("%f ", H, n, n);

    free_matrix(H);
    return 0;
}
