#include <stdio.h>
#include <math.h>
#include <string.h>
#include "array.h"
#include "problem-spec.h"

static void plot_curve(FILE *fp, double *u, int n, int steps, int k)
{
	for (int j = 0; j < n+2; j++)
		fprintf(fp, "%g %g %g\n",
				(double)k/steps, (double)j/(n+1), u[j]);
}

static double get_error(struct problem_spec *spec, double *u, int n, double T) 
{
	double err = 0.0;
	for (int j = 0; j < n+2; j++) {
		double x = spec->a + (spec->b - spec->a)/(n+1)*j;
		double diff = fabs(u[j] - spec->u_exact(x, T));
		if (diff > err)
			err = diff;
	}
	return err;
}

static void heat_explicit(struct problem_spec *spec,
		double T, int n, int steps, char *gv_filename)
{
	FILE *fp;
	double *u, *v;
	double dx = (spec->b - spec->a)/(n+1);
	double dt = T/steps;
	double r = dt/(dx*dx);
	int j, k;
	if ((fp = fopen(gv_filename, "w")) == NULL) {
		fprintf(stderr, "unable to open file `%s' for writing\n",
				gv_filename);
		return;
        }	
	fprintf(fp, "# geomview script written by the function %s()\n",
			__func__);      // begin geomview script
	fprintf(fp, "{ appearance { +edge }\n");
	fprintf(fp, "MESH %d %d\n", n+2, steps+1);
	printf("%g < x < %g;  0 < t < %g,  dx = %g, dt = %g,  "
			"r = dt/dx^2 = %g\n",
			spec->a, spec->b, T, dx, dt, r);
	if (r > 0.5)
		fprintf(stderr, "*** warning: r = dt/dx^2 = %g "
				"should be <= 0.5\n", r);
	make_vector(u, n+2);
	make_vector(v, n+2);
	for (j = 0; j < n+2; j++) {
		double x = spec->a + (spec->b - spec->a)/(n+1)*j;
		u[j] = spec->ic(x);
	}
	plot_curve(fp, u, n, steps, 0);
	for (k = 1; k <= steps; k++) {
		double *tmp;
		double t = T*k/steps;
		v[0] = spec->bcL(t);
		v[n+1] = spec->bcR(t);
		for (int j = 1; j <= n; j++)
			v[j] = r*u[j-1] + (1-2*r)*u[j] + r*u[j+1];
		tmp = v;
		v = u;
		u = tmp;
		plot_curve(fp, u, n, steps, k);
	}
	fprintf(fp, "}\n");	// end geomview script
	fclose(fp);
	printf("geomview script written to file %s\n", gv_filename);
	if (spec->u_exact != NULL) {
		double err = get_error(spec, u, n, T);
		printf("max error at time %g is %g\n", T, err);
	}
	free_vector(u);
	free_vector(v);
	putchar('\n');
}

static void show_usage(char *progname)
{
	fprintf(stderr, "Usage: %s T n s\n", progname);
	fprintf(stderr, "   T : solve over 0 <= t <= T\n");
	fprintf(stderr, "   n : grid points a=x[0], x[1], ... , x[n], x[n+1]=b\n");
	fprintf(stderr, "   s : time slices 0=t[0], t[1], ... , t[s]=T\n");
}

int main(int argc, char **argv)
{
	struct problem_spec *heat1(void);
	struct problem_spec *heat2(void);
	struct problem_spec *heat3(void);
	struct problem_spec *heat4(void);
	char *endptr;
	double T;	/* end time */
	int n, steps;
	if (argc != 4) {
		show_usage(argv[0]);
		return EXIT_FAILURE;
	}
	T = strtod(argv[1], &endptr);
	if (*endptr != '\0' || T <= 0.0) {
		show_usage(argv[0]);
		return EXIT_FAILURE;
	}
	n = strtol(argv[2], &endptr, 10);
	if (*endptr != '\0' || n < 1) {
		show_usage(argv[0]);
		return EXIT_FAILURE;
	}
	steps = strtol(argv[3], &endptr, 10);
	if (*endptr != '\0' || steps < 0) {
		show_usage(argv[0]);
		return EXIT_FAILURE;
	}
	heat_explicit(heat1(), T, n, steps, "ex1.gv");
	heat_explicit(heat2(), T, n, steps, "ex2.gv");
	heat_explicit(heat3(), T, n, steps, "ex3.gv");
	heat_explicit(heat4(), T, n, steps, "ex4.gv");
	return EXIT_SUCCESS;
}
