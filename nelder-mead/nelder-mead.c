
#include <stdio.h>
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
static inline void rank_vertices(double *v, int m,
		int *ia, int *iy, int *iz)
{
	int i;

	*ia = *iy = 0; 
	*iz = 1;
	for (i = 1; i < m; i++) {
		if (v[i] < v[*ia]) {
			*ia = i;
		} else if (v[i] >= v[*iz]) {
			*iy = *iz;
			*iz = i;
		} else if (v[i] >= v[*iy])
			*iy = i;
	}
}

/* Receives the (n+1)xn matrix s representing a simplex in R^n and computes
   the centroid C[] of the face opposite the vertex iz.  We do a bit of
   extra work to enable row-wise access to arrays.
*/
static void get_centroid(double **s, int n, int iz, double *C)
{

}

/* Given points P and Q in R^n and a scalar beta,
 * find point R such PR = beta PQ.
*/
static void inline transform(double *P, double *Q, int n, double beta, double *R)
{
	R[j] = (1 - beta)*P[j] + beta*Q[j];
}
	
/* Shrinks the simplex given by s by a factor of SHRINK toward vertex ia */
static void shrink(double **s, int n, int ia)
{
	transform(s[ia], s[i], n, SHRINK, s[i]);
}

/* replaces (swaps) row i of matrix s with vector *r */
static void inline replace_row(double **s, int i, double **r)
{

}

/* Are were there yet?
 
   The iteration is considered to have converged when:
       a) y[iz]-y[ia] drops below (h*tol)^2
   and
       b) distance between the ia and iz vertices drops below h*tol.
*/
static int done(double **s, int n,
		double *y, int ia, int iz, double err2)
{

}

int nelder_mead(struct nelder_mead *nm)
{
	double **s = nm->s;
	int n = nm->n;
	double h = nm->h;
	double tol = nm->tol;
	double err2 = (h*tol)*(h*tol);
	double *y, *C, *Pr, *Pe, *Pc;
	double yr, ye, yc;
	int ia, iy, iz;
	int simplex_to_be_freed = 0;
	int fevalcount;
	int i, j;

	make_vector(y, n+1);	// vertex values
	make_vector(Pr, n);	// the reflected point $x^{(r)}$
	make_vector(Pe, n);	// the expanded point $x^{(e)}$
	make_vector(Pc, n);	// the contracted ponts $x^{(c)}$
	make_vector(C, n);	// centroid of the face opposite vertex $iz$

	if (s == NULL) {	// build simplex if not supplied by user
		make_matrix(s, n+1, n);
		simplex_to_be_freed = 1;
		ASSIGN VALUES TO S[I][J] ...
		}
	}
	
	for (i = 0; i < n + 1; i++)
		y[i] = nm->f(s[i], n, nm->params);
	fevalcount = n+1;

	while (fevalcount <= nm->maxevals) {

		rank_vertices(y, n+1, &ia, &iy, &iz);

		if (done(s, n, y, ia, iz, err2)) {
                        COPY THE BEST VERTEX INTO THE VECTOR NM-X ...
			nm->minval = y[ia];
			break;
		}

		get_centroid(s, n, iz, C);

		transform(C, s[iz], n, -REFLECT, Pr);
		yr = nm->f(Pr, n, nm->params);
		fevalcount++;

		if (yr < y[ia]) {
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
		} else if (yr < y[iy]) {
                        CASE 2...
		} else {
			CASE 3-4 ....
		}
	}
        FREE VECTORS y, C, Pr, Pe, Pc ...
	if (simplex_to_be_freed)
		free_matrix(s);

	return fevalcount;
}
