#ifndef H_NELDER_MEAD_H
#define H_NELDER_MEAD_H 
struct nelder_mead {
	double (*f) (double *x, int n, void *params); // objective function
	int n;			// dimension of the space
	double **s;		// (n+1) x n matrix: the simplex
	double **x;		// n-vector: the iteration's starting/ending point
	double h;		// the problem's length scale
	double tol;		// tolerance; stopping criterion
	int maxevals;	// max number of evaluations
	double mineval;	// the computed minimum value
	void *params;	// parameters passed to f()
};

int nelder_mead(struct nelder_mead *nm);

#endif /* H_NELDER_MEAD_H */
