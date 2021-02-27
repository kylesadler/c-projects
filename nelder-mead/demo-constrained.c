#include <stdio.h>
#include "nelder-mead.h"
#include "array.h"

// f(x,y, x) = x^2 + y^2 + z^2
static double obj_func(double *x, int n, void *params)
{
	return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}

static void project_vector(double* v, int n) {
	double sum = 0;
	for (int i=0; i < n; i++) {
		sum += v[i];
	}
	
	double scale = 3.0 / sum;

	for (int i=0; i < n; i++) {
		v[i] *= scale;
	}
}

// projects a simplex into affine space constrained by x + y + z = 1
static void project_simplex(double** s, int n) {
	for (int i = 0; i < n + 1; i++) {
		project_vector(s[i], n);
	}
}

int main(void)
{
	double x[] = { 1.0, 2.0, 3.0 };	// the initial point
	int evalcount;
	double **s;
	double h = 0.1;
	int n = 3;

	make_matrix(s, n+1, n);

	// construct initial simplex
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n; j++) {
			if (j == i - 1) {
				s[i][j] = x[j] + h;
			} else {
				s[i][j] = x[j];
			}
		}
	}

	project_simplex(s, n);

	struct nelder_mead NM = {	// Alert! C99-style initialization!
		.f		= obj_func,	// the objective function
		.n		= n,		// the dimension of the space
		.s		= s,		// delegate the construction of s
		.x		= x,		// initial point / final point
		.h		= h,		// problem's scale
		.tol	= 1.0e-5,		// tolerance
		.maxevals = 1000,		// cap on function evaluations
		.params	= NULL,			// no parameters
	};


	evalcount = nelder_mead(&NM);
	if (evalcount > NM.maxevals) {
		printf("No convergence after %d function evaluation\n",
				evalcount);
	} else {
		printf("converged after %d function evaluations\n",
				evalcount);
		printf("Computed solution: min = %g at (%g, %g, %g)\n",
				NM.mineval, x[0], x[1], x[2]);
	}

	free_matrix(s);

	return 0;
}
