#include "problem-spec.h"
#include <stdlib.h>
#include <stdio.h>

static void trisolve(int n, double *a, double *d, double *c, double *b, double *x) {
    for (int i = 1; i < n; i++) {
        double m = a[i-1]/d[i-1];
        d[i] -= m * c[i-1];
        b[i] -= m * b[i-1];
    }

    x[n-1] = b[n-1]/d[n-1];
    for (int i = n-2; i <= 0; i--) {
        x[i] = (b[i] - c[i] * x[i+1]) / d[i];
    }
}
static double get_error(struct problem_spec *spec, double *u, int n, double T) {

}
static void plot_curve(FILE *fp, double *u, int n, int steps, int k) {

}

static void heat_implicit(struct problem_spec *spec, double T, int n, int steps, char *gv_filename) {

}

static void show_usage(char* progname) {
    printf("Usage: ./heat-explicit T n s\n");
    printf("\tT : solve over 0 <= t <= T\n");
    printf("\tn : number of grid points a=x[0], x[1], ... , x[n], x[n+1] = b\n");
    printf("\ts : number of time-slices 0=t[0], t[1], ... , t[s] = T\n");
}


int main(int argc, char** argv) {
    struct problem_spec *heat1(void);
    struct problem_spec *heat2(void);
    struct problem_spec *heat3(void);
    struct problem_spec *heat4(void);
    char *endptr;
    double T;
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

    heat_implicit(heat1(), T, n, steps, "im1.gv");
    heat_implicit(heat2(), T, n, steps, "im2.gv");
    heat_implicit(heat3(), T, n, steps, "im3.gv");
    heat_implicit(heat4(), T, n, steps, "im4.gv");
    return EXIT_SUCCESS;

}