#include <stdio.h>
#include "util.h"

void getIntFromUser(char *message, int *input) {
	printf("%s", message);
	scanf("%d", input);
}
