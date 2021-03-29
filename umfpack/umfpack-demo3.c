#include <stdio.h>
#include <umfpack.h>
#include "array.h"

static void error_and_exit(int status, const char *file, int line) {
    fprintf(stderr, "*** file %s, line %d: ", file, line);
    switch (status) {
        case UMFPACK_ERROR_out_of_memory:
            fprintf(stderr, "out of memory!\n");
            break;
        case UMFPACK_WARNING_singular_matrix:
            fprintf(stderr, "matrix is singular!\n");
            break;
        default:
            fprintf(stderr, "UMFPACK error code %d\n", status);
    }
    exit(EXIT_FAILURE);
}

int main(void)
{
	void *Symbolic, *Numeric;
	double *b, *x, *Ax;;
	int *Ap, *Ai;
	int n = 5;
    int status;

    int N = 20; // N = 20 is an overestimate; N = 12 will do
    int k = 0;
    int *Ti, *Tj;
    double *Tx;

    make_vector(x, n);
    
    // create matrix
    make_vector(Ti, N);
    make_vector(Tj, N);
    make_vector(Tx, N);

    Ti[k] = 0; Tj[k] = 0; Tx[k] = 2.0; k++; // (0,0) entry is 2.0
    Ti[k] = 0; Tj[k] = 1; Tx[k] = 3.0; k++; // (0,1) entry is 3.0

    Ti[k] = 1; Tj[k] = 0; Tx[k] = 3.0; k++; // (1,0) entry is 3.0
    Ti[k] = 1; Tj[k] = 2; Tx[k] = 4.0; k++;
    Ti[k] = 1; Tj[k] = 4; Tx[k] = 6.0; k++;

    Ti[k] = 2; Tj[k] = 1; Tx[k] = -1.0; k++;
    Ti[k] = 2; Tj[k] = 2; Tx[k] = -3.0; k++;
    Ti[k] = 2; Tj[k] = 3; Tx[k] = 2.0; k++;

    Ti[k] = 3; Tj[k] = 2; Tx[k] = 1.0; k++;

    Ti[k] = 4; Tj[k] = 1; Tx[k] = 4.0; k++;
    Ti[k] = 4; Tj[k] = 2; Tx[k] = 2.0; k++;
    Ti[k] = 4; Tj[k] = 4; Tx[k] = 1.0; k++;


    // create b
    make_vector(b, n);
    b[0] = 8; b[1] = 45; b[2] = -3; b[3] = 3; b[4] = 19;


    // .4. print out a, b, and nz as in Project Sparse Matrix ...
    printf("b =   ");
    print_vector(" %5g", b, n);
    printf("\n");


    // 5. allocate memory for the vectors Ap, Ai, and Ax
    make_vector(Ax, N);
    make_vector(Ai, N);
    make_vector(Ap, n+1);

    
	// sparse_pack(a, n, n, Ap, Ai, Ax);
    status = umfpack_di_triplet_to_col(n, n, N, Ti, Tj, Tx, Ap, Ai, Ax, NULL);
    if (status != UMFPACK_OK) {
        error_and_exit(status, __FILE__, __LINE__);
    }


    // 6. print out Ap, Ai, Ax ...
    printf("Ap =  ");
    print_vector(" %5d", Ap, n+1);
    printf("Ai =  ");
    print_vector(" %5d", Ai, N);
    printf("Ax =  ");
    print_vector(" %5g", Ax, N);
    printf("\n");


    status = umfpack_di_symbolic(n, n, Ap, Ai, Ax, &Symbolic, NULL, NULL);
    if (status != UMFPACK_OK) {
        error_and_exit(status, __FILE__, __LINE__);
    }

	status = umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, NULL, NULL);
    if (status != UMFPACK_OK) {
        error_and_exit(status, __FILE__, __LINE__);
    }
    
    status = umfpack_di_solve(UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, NULL, NULL);
    if (status != UMFPACK_OK) {
        error_and_exit(status, __FILE__, __LINE__);
    }

    // 7. print out x ...
    printf("\nx =   ");
    print_vector(" %5g", x, n);


	umfpack_di_free_symbolic(&Symbolic);
	umfpack_di_free_numeric(&Numeric);
 

    // 8. free allocated vectors
    free_vector(Ti);
    free_vector(Tj);
    free_vector(Tx);
    free_vector(b);
    free_vector(x);

    free_vector(Ax);
    free_vector(Ai);
    free_vector(Ap);

	return 0;
}
