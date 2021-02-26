/* xmalloc.c
 *
 * malloc_or_exit() is a front-end to the Standard Library's malloc().
 *
 * Its purpose to distinguish between successful and unsuccessful
 * calls malloc().  If successul, it returns the memory address
 * allocated by malloc() to the calling function.  If unsuccessful, it
 * prints a message to stderr and calls exit().
 *
 * 2012-09-19
*/

#include <stdio.h>
#include "xmalloc.h"

/* IMPORTANT!
This function is NOT INCLUDED literally in the book.
A version without the "nbytes == 0" is.  The addition
of that check is left as a project item.
*/

void *malloc_or_exit(size_t nbytes, const char *file, int line)
{
	void *x;
	if (nbytes == 0 || (x = malloc(nbytes)) == NULL) {
		fprintf(stderr, "%s:line %d: malloc() of %zu bytes failed\n",
				file, line, nbytes);
		exit(EXIT_FAILURE);
	} else
		return x;
}

