#include "array.h"
#include <stdio.h>

void test_vector(int n) {
    int * vector;
    printf("Creating vector...\n");
    make_vector(vector, n);
    
    for (int i = 0; i < n; i++) {
        vector[i] = i * 1.0;
    }

    printf("Printing vector:\n");
    print_vector("%d ", vector, n);

    printf("Freeing vector...\n");
    free_vector(vector);
    
    printf("Vector PASSED\n\n");
}

void test_matrix(int n) {
    int ** matrix;
    printf("Creating matrix...\n");
    make_matrix(matrix, n, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i * 10 + j;
        }
    }

    printf("Printing matrix:\n");
    print_matrix("%02d ", matrix, n, n);

    printf("Freeing matrix...\n");
    free_matrix(matrix);

    printf("Matrix PASSED\n\n");
}

void test_3array(int n) {
    int *** array3;

    printf("Creating 3array...\n");
    make_3array(array3, n, n, n);
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                array3[i][j][k] = i * 100 + j * 10 + k;
            }
        }
    }

    printf("Printing 3array:\n");
    print_3array("%03d ", array3, n, n, n);

    printf("Freeing 3array...\n");
    free_3array(array3);

    printf("3array PASSED\n\n");
}

void test_4array(int n) {
    int **** array4;

    printf("Creating 4array...\n");
    make_4array(array4, n, n, n, n);
    
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    array4[i][j][k][l] = i * 1000 + j * 100 + k * 10 + l;
                }
            }
        }
    }

    printf("Printing 4array:\n");
    print_4array("%04d ", array4, n, n, n, n);

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
