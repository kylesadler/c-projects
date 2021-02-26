int nelder_mead(struct nelder_mead *nm) {
	double **s = nm->s;
	int n = nm-> n;
	double tol = nm->tol;
	double err2 = (h*tol)*(h*tol);
	double *y, *C, *Pr, *Pe, *Pc;
	double yr, ye, yc;
	int ia, iy, iz;
	int simplex_to_be_freed = 0;
	int fevalcount;
	int i, j;

	make_vector(y, n + 1); // vertex values
        make_vector(Pr, n); // reflected point $x^(r)$
        make_vector(Pe, n); // expanded point $x^(e)$
        make_vector(Pc, n); // contracted point $x^(c)$

}

