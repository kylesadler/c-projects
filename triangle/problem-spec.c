#include "problem_spec.h"
#include "array.h"
#include "xmalloc.h"

struct problem_spec *triangle_with_hole(void) {
    static struct problem_spec_point points[] = {
        // triangle vertices
        { 0, -1.0,  0.0, FEM_BC_DIRICHLET },
        { 1,  1.0,  0.0, FEM_BC_DIRICHLET },
        { 2,  0.0,  2.0, FEM_BC_DIRICHLET },

        // hole vertices
        { 3, -0.25, 0.25, FEM_BC_DIRICHLET },
        { 4, +0.25, 0.25, FEM_BC_DIRICHLET },
        { 5, +0.25, 1.0 , FEM_BC_DIRICHLET },
        { 6, -0.25, 1.0 , FEM_BC_DIRICHLET },
    };

    static struct problem_spec_segment segments[] = {
        // triangle
        { 0, 0, 1, FEM_BC_DIRICHLET },
        { 1, 1, 2, FEM_BC_DIRICHLET },
        { 2, 2, 0, FEM_BC_DIRICHLET },

        // hole
        { 3, 3, 4, FEM_BC_DIRICHLET },
        { 4, 4, 5, FEM_BC_DIRICHLET },
        { 5, 5, 6, FEM_BC_DIRICHLET },
        { 6, 6, 3, FEM_BC_DIRICHLET },
    };

    static struct problem_spec_hole holes[] = {
        { 0.0, 0.75 };
    };

    static struct problem_spec spec = {
        .points = points,
        .segments = segments,
        .holes = holes,
        .npoints = sizeof points / sizeof points[0],
        .nsegments = sizeof segments / sizeof segments[0],
        .nholes = sizeof holes / sizeof holes[0],
        .f = NULL,
        .g = NULL,
        .h = NULL,
        .eta = NULL,
        .u_exact = NULL,
    };

    printf("domain is a triangle with hole\n");
    return &spec;

}

struct problem_spec *annulus(int n) {

    double Pi = 4*atan(1);
    double a = 0.325, b = 2*a;
    struct problem_spec *spec = xmalloc(sizeof *spec);
    make_vector(spec->points, 2*n);
    make_vector(spec->segments, 2*n);
    make_vector(spec->holes, 1);

    for (int i = 0; i < n; i++) {
        double t = 2*i*Pi/n;

        spec->points[i].point_no = i;
        spec->points[i].x = a*cos(t);
        spec->points[i].y = a*sin(t);
        spec->points[i].bc = FEM_BC_DIRICHLET;
        spec->points[i+n].point_no = i+n;
        spec->points[i+n].x = b*cos(t);
        spec->points[i+n].y = b*sin(t);
        spec->points[i+n].bc = FEM_BC_DIRICHLET;
    }

    for (int i = 0; i < n; i++) {
        double t = 2*i*Pi/n;

        spec->segments[i].segment_no = i;
        spec->segments[i].point_no_1 = i;
        spec->segments[i].point_no_2 = i+1;
        spec->segments[i].bc = FEM_BC_DIRICHLET;
        spec->segments[i+n].segment_no = i+n;
        spec->segments[i+n].point_no_1 = i+n;
        spec->segments[i+n].point_no_2 = i+n+1;
        spec->segments[i+n].bc = FEM_BC_DIRICHLET;
    }

    spec->segments[n-1].point_no_2 -= n;
    spec->segments[2*n-1].point_no_2 -= n;

    spec->holes[0].x = spec->holes[0].y = 0.0;

    spec->npoints = 2*n;
    spec->nsegments = 2*n;
    spec->nholes = 1;
    spec->f = spec->g = spec->h = spec->eta = spec->u_exact = NULL;

    printf("domain is an annulus (really a %d-gon) or radii %g and %g\n", n, a, b);
    return spec;

}

void free_annulus(struct problem_spec *spec) {
    if (spec != NULL) {
        free_vector(spec->points);
        free_vector(spec->segments);
        free_vector(spec->holes);
        free(spec);
    }
}



struct problem_spec *square(void) {
    static struct problem_spec_point points[] = {
        // triangle vertices
        { 0, -1.0,  0.0, FEM_BC_DIRICHLET },
        { 1,  1.0,  0.0, FEM_BC_DIRICHLET },
        { 2,  0.0,  2.0, FEM_BC_DIRICHLET },

        // hole vertices
        { 3, -0.25, 0.25, FEM_BC_DIRICHLET },
        { 4, +0.25, 0.25, FEM_BC_DIRICHLET },
        { 5, +0.25, 1.0 , FEM_BC_DIRICHLET },
        { 6, -0.25, 1.0 , FEM_BC_DIRICHLET },
    };

    static struct problem_spec_segment segments[] = {
        // triangle
        { 0, 0, 1, FEM_BC_DIRICHLET },
        { 1, 1, 2, FEM_BC_DIRICHLET },
        { 2, 2, 0, FEM_BC_DIRICHLET },

        // hole
        { 3, 3, 4, FEM_BC_DIRICHLET },
        { 4, 4, 5, FEM_BC_DIRICHLET },
        { 5, 5, 6, FEM_BC_DIRICHLET },
        { 6, 6, 3, FEM_BC_DIRICHLET },
    };

    static struct problem_spec_hole holes[] = {
        { 0.0, 0.75 };
    };

    static struct problem_spec spec = {
        .points = points,
        .segments = segments,
        .holes = holes,
        .npoints = sizeof points / sizeof points[0],
        .nsegments = sizeof segments / sizeof segments[0],
        .nholes = sizeof holes / sizeof holes[0],
        .f = NULL,
        .g = NULL,
        .h = NULL,
        .eta = NULL,
        .u_exact = NULL,
    };

    printf("domain is a triangle with hole\n");
    return &spec;

}

struct problem_spec *three_holes(void) { }
void free_three_holes(struct problem_spec *spec) { }