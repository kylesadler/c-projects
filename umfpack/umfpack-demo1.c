#include <stdio.h>
#include <umfpack.h>
#include "sparse.h"
#include "array.h"

int main(void)
{
	void *Symbolic, *Numeric;
	double **a;
	double *b, *x, *Ax;;
	int *Ap, *Ai;
	int n = 5;

	// 1. allocate memory for the matrix a and the vectors b and x
    make_matrix(a, n, n);
    make_vector(b, n);
    make_vector(x, n);

    // 2. populate the matrix a and vector b with the given numbers
    a[0][0] = 2; a[0][1] = 3; a[0][2] = 0; a[0][3] = 0; a[0][4] = 0;
    a[1][0] = 3; a[1][1] = 0; a[1][2] = 4; a[1][3] = 0; a[1][4] = 6;
    a[2][0] = 0; a[2][1] = -1; a[2][2] = -3; a[2][3] = 2; a[2][4] = 0;
    a[3][0] = 0; a[3][1] = 0; a[3][2] = 1; a[3][3] = 0; a[3][4] = 0;
    a[4][0] = 0; a[4][1] = 4; a[4][2] = 2; a[4][3] = 0; a[4][4] = 1;

    
    b[0] = 8; b[1] = 45; b[2] = -3; b[3] = 3; b[4] = 19;


    // 3. compute nz as in Project Sparse Matrix
    int nz = 0;
    for (int i = 0; i < n; i++)
       for (int j = 0; j < n; j++)
            if (a[i][j] != 0.0)
                nz++;



    // .4. print out a, b, and nz as in Project Sparse Matrix ...
    printf("A is\n");
    print_matrix(" %5g", a, n, n);
    printf("matrix is %dx%d, nz = %d\n\n", n, n, nz);

    printf("b =   ");
    print_vector(" %5g", b, n);
    printf("\n");


    // 5. allocate memory for the vectors Ap, Ai, and Ax
    make_vector(Ax, nz);
    make_vector(Ai, nz);
    make_vector(Ap, n+1);



	sparse_pack(a, n, n, Ap, Ai, Ax);
    

    // 6. print out Ap, Ai, Ax ...
    printf("Ap =  ");
    print_vector(" %5d", Ap, n+1);
    printf("Ai =  ");
    print_vector(" %5d", Ai, nz);
    printf("Ax =  ");
    print_vector(" %5g", Ax, nz);
    printf("\n");


	umfpack_di_symbolic(n, n, Ap, Ai, Ax, &Symbolic, NULL, NULL);
	umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, NULL, NULL);
	umfpack_di_solve(UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, NULL, NULL);


    // 7. print out x ...
    printf("\nx =   ");
    print_vector(" %5g", x, n);


	umfpack_di_free_symbolic(&Symbolic);
	umfpack_di_free_numeric(&Numeric);
 

    // 8. also free the allocated memory for a, b, x, Ap, Ai, Ax ...
    free_matrix(a);
    free_vector(b);
    free_vector(x);

    free_vector(Ax);
    free_vector(Ai);
    free_vector(Ap);

	return 0;
}
