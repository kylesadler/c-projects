#include <stdio.h>
#include "sparse.h"
#include "array.h"

int main(void)
{
    double **a; 
    int m = 4, n = 5;
    int i, j, nz;

    make_matrix(a, 4, 5);

    a[0][0] = 0; a[0][1] = 7; a[0][2] = 0; a[0][3] = 0; a[0][4] = 1;
    a[1][0] = 0; a[1][1] = 4; a[1][2] = 0; a[1][3] = 3; a[1][4] = 0;
    a[2][0] = 6; a[2][1] = 6; a[2][2] = 5; a[2][3] = 1; a[2][4] = 4;
    a[3][0] = 5; a[3][1] = 5; a[3][2] = 0; a[3][3] = 0; a[3][4] = 0;

    nz = 0;
    for (i = 0; i < m; i++)
       for (j = 0; j < n; j++)
            if (a[i][j] != 0.0)
                nz = nz + 1; // nz++;

   print_matrix("%g ", a, 4, 5);
 
	make_vector(Ap, n+1);
	make_vector(Ap, n+1);
	make_vector(Ap, n);

	free_matrix(a);
	free_matrix(b);
	free_matrix(c);


 return 0;  
} 
