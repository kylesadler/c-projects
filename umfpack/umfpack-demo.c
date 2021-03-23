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
	int i, j, nz;

	.1. allocate memory for the matrix a and the vectors b and x
        .2. populate the matrix a and vector b with the given numbers
        .3. compute nz as in Project Sparse Matrix
        .4. print out a, b, and nz as in Project Sparse Matrix ...
        .5. allocate memory for the vectors Ap, Ai, and Ax

	sparse_pack(a, n, n, Ap, Ai, Ax);

        .6. print out Ap, Ai, Ax ...

	umfpack_di_symbolic(n, n, Ap, Ai, Ax, &Symbolic, NULL, NULL);
	umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, NULL, NULL);
	umfpack_di_solve(UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, NULL, NULL);

        .7. print out x ...

	umfpack_di_free_symbolic(&Symbolic);
	umfpack_di_free_numeric(&Numeric);
 
        .8. also free the allocated memory for a, b, x, Ap, Ai, Ax ...

	return 0;
}
