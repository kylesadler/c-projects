#include "xmalloc.h"
#include <stdio.h>

void allocateAndFree(int numBytes) {
    void *x = xmalloc(numBytes);
    printf("Allocated %d bytes.\n", numBytes);
    free(x);
    printf("Freed %d bytes.\n", numBytes);
}


int main() {
    allocateAndFree(1000);
    allocateAndFree(0);
}
