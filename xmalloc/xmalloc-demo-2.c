#include "xmalloc.h"
#include <stdio.h>
#include <stdbool.h>

int main () {
    int numBytes = 1000000;
    while(true) {
        printf("Allocating %d bytes.\n", numBytes);
        xmalloc(numBytes);
    }
}
