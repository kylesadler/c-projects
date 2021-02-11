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

void test_vector(int n) {
    double * vector;
    printf("Creating vector...\n");
    make_vector(vector, n);
    
    for (int i = 0; i < n; i++) {
        vector[i] = i * 2.0;
    }

    printf("Printing vector:\n");
    print_vector("%f ", vector, n);

    printf("Freeing vector...\n");
    free_vector(vector);
    
    printf("Vector PASSED\n\n");
}

void test_matrix(int n) {
    double ** matrix;
    printf("Creating matrix...\n");
    make_matrix(matrix, n, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i * 2.0 / (j + 1.0);
        }
    }

    printf("Printing matrix:\n");
    print_matrix("%f ", matrix, n, n);

    printf("Freeing matrix...\n");
    free_matrix(matrix);

    printf("Matrix PASSED\n\n");
}

void test_3array(int n) {
    double *** array3;

    printf("Creating 3array...\n");
    make_3array(array3, n, n, n);
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                array3[i][j][k] = i * k / (j + 1.0);
            }
        }
    }

    printf("Printing 3array:\n");
    print_3array("%f ", array3, n, n, n);

    printf("Freeing 3array...\n");
    free_3array(array3);

    printf("3array PASSED\n\n");
}

void test_4array(int n) {
    double **** array4;

    printf("Creating 4array...\n");
    make_4array(array4, n, n, n, n);
    
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    array4[i][j][k][l] = i * k / (j + 1.0 + l);
                }
            }
        }
    }

    printf("Printing 4array:\n");
    print_4array("%f ", array4, n, n, n, n);

    printf("Freeing 4array...\n");
    free_4array(array4);

    printf("4array PASSED\n\n");
}

int main() {

    int n = 2;
    
    test_vector(n);
    test_matrix(n);
    test_3array(n);
    test_4array(n);
    
    return 0;
}
