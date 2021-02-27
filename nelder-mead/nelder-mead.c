
#include <stdio.h>
#include <math.h>
#include "array.h"
#include "nelder-mead.h"

#define REFLECT		1.0
#define EXPAND		2.0
#define CONTRACT	0.5
#define SHRINK		0.5

/* Receives a vector v of length m (m = n + 1, where n is the dimension of
   the space,) and computes the indices iz, iy, ia corresponding to the highest,
   next-to-highest and lowest entries.
*/
static inline void rank_vertices(double *v, int m, int *ia, int *iy, int *iz) {
	/*  initialize ia, iy, iz  */
	if (v[0] > v[1]) {
		*ia = 1;
		*iy = 1;
		*iz = 0;
	} else {
		*ia = 0;
		*iy = 0;
		*iz = 1;
	}

	/*  try to find better ia, iy, iz  */
	for (int i = 0; i < m; i++) {
		if (v[i] < v[*ia])
			*ia = i;
		
		if (v[i] > v[*iz]) {
			*iy = *iz;
			*iz = i;
		}
		
		if (v[i] >= v[*iy] && *iz != i)
			*iy = i;
	}
}

/* Receives the (n+1)xn matrix s representing a simplex in R^n and computes
   the centroid C[] of the face opposite the vertex iz.  We do a bit of
   extra work to enable row-wise access to arrays.
*/
static void get_centroid(double **s, int n, int iz, double *C) {
	for (int j = 0; j < n; j++) {
		C[j] = 0;
	}

	for (int i = 0; i < n+1; i++) {
		if (i != iz) {
			for (int j = 0; j < n; j++) {
				C[j] += s[i][j];
			}
		} 
	}

	for (int j = 0; j < n; j++) {
		C[j] /= n;
	}
}

/* Given points P and Q in R^n and a scalar beta,
 * find point R such PR = beta PQ.
*/
static inline void transform(double *P, double *Q, int n, double beta, double *R) {
	for (int j = 0; j < n; j++) {
		R[j] = (1 - beta)*P[j] + beta*Q[j];
	}
}
	
/* Shrinks the simplex given by s by a factor of SHRINK toward vertex ia */
static void shrink(double **s, int n, int ia) {
	for (int i = 0; i < n + 1; i++) {
		if (i != ia) {
			transform(s[ia], s[i], n, SHRINK, s[i]);
		}
	}
}

/* replaces (swaps) row i of matrix s with vector *r */
static void inline replace_row(double **s, int i, double **r) {
	double* temp = s[i];
	s[i] = *r;
	*r = temp;
}


static double distanceSquared(double* a, double* b, int n) {
	double output = 0;
	for (int i = 0; i < n; i++) {
		output += (a[i]-b[i]) * (a[i]-b[i]);
	}
	return output;
}

/* Are were there yet?
 
   The iteration is considered to have converged when:
       a) y[iz]-y[ia] drops below (h*tol)^2
   and
       b) distance between the ia and iz vertices drops below h*tol.
*/
static int done(double **s, int n, double *y, int ia, int iz, double err2) {
	return distanceSquared(s[iz], s[ia], n) < err2 && fabs(y[iz] - y[ia]) <= err2;
}


int nelder_mead(struct nelder_mead *nm) {
	double **s = nm->s;
	int n = nm->n;
	double* x = nm->x;
	double h = nm->h;
	double tol = nm->tol;
	double err2 = (h*tol)*(h*tol);
	double *y, *C, *Pr, *Pe, *Pc;
	double yr, ye, yc;
	int ia, iy, iz;
	int simplex_to_be_freed = 0;
	int fevalcount;

	// temporary variables for cases 3 + 4
	double* point;
	double y_value;

	make_vector(y, n+1);	// vertex values
	make_vector(Pr, n);	// the reflected point $x^{(r)}$
	make_vector(Pe, n);	// the expanded point $x^{(e)}$
	make_vector(Pc, n);	// the contracted ponts $x^{(c)}$
	make_vector(C, n);	// centroid of the face opposite vertex $iz$

	if (s == NULL) {	// build simplex if not supplied by user
		make_matrix(s, n+1, n);
		simplex_to_be_freed = 1;

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

		// print_vector("%f ", x, n);
		// printf("%f %f\n", x[0], x[1]);
		// printf("%f \n", h);
		// print_matrix("%f ", s, n+1, n);
	}
	
	for (int i = 0; i < n + 1; i++)
		y[i] = nm->f(s[i], n, nm->params);
	fevalcount = n+1;
	// print_vector("%f ", y, n+1);

	while (fevalcount <= nm->maxevals) {

		rank_vertices(y, n+1, &ia, &iy, &iz);
		// printf("%d %d %d\n", ia, iy, iz);

		if (done(s, n, y, ia, iz, err2)) {
			// COPY THE BEST VERTEX INTO THE VECTOR NM-X ...
			for (int i = 0; i < n; i++) {
				nm->x[i] = s[ia][i];
			}
			nm->mineval = y[ia];
			break;
		}

		get_centroid(s, n, iz, C);

		transform(C, s[iz], n, -REFLECT, Pr);
		yr = nm->f(Pr, n, nm->params);
		fevalcount++;

		if (yr < y[ia]) { // CASE 1...
			transform(C, Pr, n, EXPAND, Pe);
			ye = nm->f(Pe, n, nm->params);
			fevalcount++;
			if (ye < yr) {
				replace_row(s, iz, &Pe);
				y[iz] = ye;
			} else {
				replace_row(s, iz, &Pr);
				y[iz] = yr;
			}
		
		} else if (yr < y[iy]) { // CASE 2...
			replace_row(s, iz, &Pr);
			y[iz] = yr;

		} else { // CASE 3-4...

			if (yr < y[iz]) {	// CASE 3
				point = Pr;
				y_value = yr;
			} else {			// CASE 4
				point = s[iz];
				y_value = y[iz];
			}

			transform(C, point, n, CONTRACT, Pc);
			yc = nm->f(Pc, n, nm->params);
			fevalcount++;

			if (yc < y_value) {
				replace_row(s, iz, &Pc);
				y[iz] = yc;
			} else {
				shrink(s, n, ia);
				for (int i = 0; i < n + 1; i++) {
					if (i != ia) {
						y[i] = nm->f(s[i], n, nm->params);
						fevalcount++;
					}
				}
			}

		}
	}
    
	//    FREE VECTORS y, C, Pr, Pe, Pc ...
	free_vector(y);
	free_vector(Pr);
	free_vector(Pe);
	free_vector(Pc);
	free_vector(C);

	if (simplex_to_be_freed)
		free_matrix(s);

	return fevalcount;
}
