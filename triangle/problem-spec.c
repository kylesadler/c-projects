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