#include "problem-spec.h"
#include "array.h"
#include "xmalloc.h"
#include <stdio.h>
#include <math.h>

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
        { 0.0, 0.75 }
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
        
        // points
        double t = 2*i*Pi/n;
        spec->points[i].point_no = i;
        spec->points[i].x = a*cos(t);
        spec->points[i].y = a*sin(t);
        spec->points[i].bc = FEM_BC_DIRICHLET;
        spec->points[i+n].point_no = i+n;
        spec->points[i+n].x = b*cos(t);
        spec->points[i+n].y = b*sin(t);
        spec->points[i+n].bc = FEM_BC_DIRICHLET;
        
        // segments
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
        { 0, 0.0,  0.0, FEM_BC_DIRICHLET },
        { 1, 1.0,  0.0, FEM_BC_DIRICHLET },
        { 2, 1.0,  1.0, FEM_BC_DIRICHLET },
        { 3, 0.0,  1.0, FEM_BC_DIRICHLET },
    };

    static struct problem_spec_segment segments[] = {
        { 0, 0, 1, FEM_BC_DIRICHLET },
        { 1, 1, 2, FEM_BC_DIRICHLET },
        { 2, 2, 3, FEM_BC_DIRICHLET },
        { 3, 3, 0, FEM_BC_DIRICHLET },
    };

    static struct problem_spec spec = {
        .points = points,
        .segments = segments,
        .holes = NULL,
        .npoints = sizeof points / sizeof points[0],
        .nsegments = sizeof segments / sizeof segments[0],
        .nholes = 0,
        .f = NULL,
        .g = NULL,
        .h = NULL,
        .eta = NULL,
        .u_exact = NULL,
    };

    printf("domain is a square\n");
    return &spec;

}

struct problem_spec *three_holes(int n) {
    // n is number of sides on holes

    double Pi = 4*atan(1);
    double s = 0.64; //1;
    double radius = s/4;
    struct problem_spec *spec = xmalloc(sizeof *spec);

    spec->npoints = 3*n + 6;
    spec->nsegments = 3*n + 6;
    spec->nholes = 3;

    make_vector(spec->points, spec->npoints);
    make_vector(spec->segments, spec->nsegments);
    make_vector(spec->holes, spec->nholes);

    // create piece outline
    for (int i = 0; i < 6; i++) {
        spec->points[i].point_no = i;
        spec->points[i].bc = FEM_BC_DIRICHLET;

        spec->segments[i].segment_no = i;
        spec->segments[i].point_no_1 = i;
        spec->segments[i].point_no_2 = i+1;
        spec->segments[i].bc = FEM_BC_DIRICHLET;
    }

    spec->segments[5].point_no_2 -= 6;

    spec->points[0].x = -s;
    spec->points[0].y = -s;

    spec->points[1].x = 0.0;
    spec->points[1].y = -s;

    spec->points[2].x = 0.0;
    spec->points[2].y = 0.0;

    spec->points[3].x = s;
    spec->points[3].y = 0.0;

    spec->points[4].x = s;
    spec->points[4].y = s;
    
    spec->points[5].x = -s;
    spec->points[5].y = s;



    // create holes
    double holeX[] = { -s/2, -s/2, s/2 };
    double holeY[] = { -s/2, s/2, s/2 };

    for (int holeNum = 0; holeNum < 3; holeNum++) {

        spec->holes[holeNum].x = holeX[holeNum];
        spec->holes[holeNum].y = holeY[holeNum];

        int startIdx = holeNum*n + 6;
        int endIdx = startIdx + n;

        for (int i = startIdx; i < endIdx; i++) {
            double t = 2*(i-startIdx)*Pi/n;

            spec->points[i].point_no  = i;
            spec->points[i].x         = spec->holes[holeNum].x + radius*cos(t);
            spec->points[i].y         = spec->holes[holeNum].y + radius*sin(t);
            spec->points[i].bc        = FEM_BC_DIRICHLET;

            spec->segments[i].segment_no = i;
            spec->segments[i].point_no_1 = i;
            spec->segments[i].point_no_2 = i+1;
            spec->segments[i].bc = FEM_BC_DIRICHLET;
        }

        spec->segments[endIdx-1].point_no_2 -= n;
    }

    spec->f = spec->g = spec->h = spec->eta = spec->u_exact = NULL;

    printf("domain is an L-shape with three holes (actually %d-gons)\n", n);
    return spec;

}

void free_three_holes(struct problem_spec *spec) {
    if (spec != NULL) {
        free_vector(spec->points);
        free_vector(spec->segments);
        free_vector(spec->holes);
        free(spec);
    }
}
