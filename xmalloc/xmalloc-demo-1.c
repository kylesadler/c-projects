#include "xmalloc.h"
#include <stdio.h>

void allocateAndFree(int numBytes) {
    printf("Allocating %d bytes.\n", numBytes);
    void *x = xmalloc(numBytes);
    free(x);
    printf("Freed %d bytes.\n", numBytes);
}

int main() {
    allocateAndFree(1000);
    allocateAndFree(0);
}
