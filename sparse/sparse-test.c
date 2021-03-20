#include <stdio.h>
#include "sparse.h"
#include "array.h"

int main(void)
{
    int m = 4;
    int n = 5;

    double **a, **b, **c;
    double *Ax;
    int *Ap, *Ai;

    make_matrix(a, m, n);
    make_matrix(b, m, n);
    make_matrix(c, m, n);

    a[0][0] = 0; a[0][1] = 7; a[0][2] = 0; a[0][3] = 0; a[0][4] = 1;
    a[1][0] = 0; a[1][1] = 4; a[1][2] = 0; a[1][3] = 3; a[1][4] = 0;
    a[2][0] = 6; a[2][1] = 6; a[2][2] = 5; a[2][3] = 1; a[2][4] = 4;
    a[3][0] = 5; a[3][1] = 5; a[3][2] = 0; a[3][3] = 0; a[3][4] = 0;

    int nz = 0;
    for (int i = 0; i < m; i++)
       for (int j = 0; j < n; j++)
            if (a[i][j] != 0.0)
                nz++;

    printf("The sparse matrix is\n");
    print_matrix("\t%g", a, m, n);
    printf("matrix is %dx%d, nz = %d\n", m, n, nz);

    make_vector(Ax, nz);
    make_vector(Ai, nz);
    make_vector(Ap, n+1);

    sparse_pack(a, m, n, Ap, Ai, Ax);
    
    // print Ap, Ai, Ax
    printf("\nAp =   ");
    print_vector("   %d", Ap, n+1);
    printf("Ai =   ");
    print_vector("   %d", Ai, nz);
    printf("Ax =   ");
    print_vector("   %g", Ax, nz);
    printf("\n");

    sparse_unpack(b, m, n, Ap, Ai, Ax);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] - b[i][j];

    printf("The difference of the original and reconstructed matrices:\n");
    print_matrix("\t%g", c, m, n);

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);

    free_vector(Ax);
    free_vector(Ai);
    free_vector(Ap);
 
    return 0;  
} 
