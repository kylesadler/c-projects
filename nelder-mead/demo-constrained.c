#include <stdio.h>
#include "nelder-mead.h"

// f(x,y, x) = x^2 + y^2 + z^2
static double obj_func(double *x, int n, void *params)
{
	return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}

// TODO 
int main(void)
{
	double x[] = { 0.0, 0.0 };	// the initial point
	int evalcount;
	struct nelder_mead NM = {	// Alert! C99-style initialization!
		.f		= obj_func,	// the objective function
		.n		= 2,		// the dimension of the space
		.s		= NULL,		// delegate the construction of s
		.x		= x,		// initial point / final point
		.h		= 0.1,		// problem's scale
		.tol	= 1.0e-4,		// tolerance
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
		printf("Computed solution: min = %g at (%g, %g)\n",
				NM.minval, x[0], x[1]);
	}
	return 0;
}
