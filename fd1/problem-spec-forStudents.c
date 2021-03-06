#include <stdio.h>
#include <math.h>
#include "problem-spec.h"

// heat1( ): quite a basic 1-D heat equation with exact solution
static double heat1_exact(double x, double t)
{
	double Pi = 4*atan(1);
	return exp(-Pi*Pi/4*t) * cos(Pi/2*x);
}

static double heat1_ic(double x)
{
	return heat1_exact(x,0);
}

static double heat1_bcL(double t)
{
	return heat1_exact(-1,t);
}

static double heat1_bcR(double t)
{
	return heat1_exact(1,t);
}

struct problem_spec *heat1(void)
{
	static struct problem_spec spec = {	// C99-style initialization!
		.a		= -1.0,
		.b		=  1.0,
		.ic		= heat1_ic,
		.bcL		= heat1_bcL,
		.bcR		= heat1_bcR,
		.u_exact	= heat1_exact,
	};
	printf("problem heat1:\n");
	return &spec;
}

