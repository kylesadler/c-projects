/* We #include stdlib.h here for at least two reason:

1. It defines the type size_t.  We could have includes stddef.h instead
   for that purpuse, but see next.

2. It has the prototype for free().  It's likely that a program that
   calls xmalloc(), will eventually call free() to free the allocated
   memory.
*/

#ifndef H_XMALLOC_H
#define H_XMALLOC_H
#include <stdlib.h>
void *malloc_or_exit(size_t nbytes, const char *file, int line);
#define xmalloc(nbytes)  malloc_or_exit((nbytes), __FILE__, __LINE__)
#endif /* H_XMALLOC_H */

