#include <stdio.h>
#include "sparse.h"
#include "array.h"

void sparse_unpack(double **a, int m, int n, int *Ap, int *Ai, double *Ax) {
	int i, j, k;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			a[i][j] = 0.0;

	for (j = 0; j < n; j++)
		for (k = Ap[j]; k < Ap[j+1]; k++) {
			i = Ai[k];
			a[i][j] = Ax[k];
		}
}

/* a[m][n] 
	Ai and Ax are length of number of nonzero entries in a
	Ap is length n
	Ax values
	Ai column indices
*/
void sparse_pack(double **a, int m, int n, int *Ap, int *Ai, double *Ax) {
	int nz = 0; // number of non-zero entries found so far


	// loop over columns
	for (int j = 0; j < n; j++) {
		int nonzero_found = 0; // boolean; if we have found a nonzero entry this column
		for (int i = 0; i < m; i++) {
			if(a[i][j] != 0) {
				Ax[nz] = a[i][j];

				if (nonzero_found == 0) {
					Ap[j] = nz;
					nonzero_found = 1;
				}

				Ai[nz++] = i;
			}
		}

		// todo check this
		if (nonzero_found == 0)
			Ap[j+1] = nz;
	}

	Ap[n] = nz;
}
