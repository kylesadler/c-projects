#include <stdio.h>
#include "sparse.h"
#include "array.h"

void sparse_unpack(double **a, int m, int n,
		int *Ap, int *Ai, double *Ax)
{
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

