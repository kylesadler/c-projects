#include <string.h>
#include <stdio.h>
#include "util.h"

int getIntFromUser(char *message, int *location) {
	printf("%s", message);
	scanf("%d", location);
}

