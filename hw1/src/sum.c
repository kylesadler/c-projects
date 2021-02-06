#include <stdio.h>
#include "util.h"

int main() {
	printf("This program computes the sum of the first n positive integers.\n");

	int n;
	getIntFromUser("Enter n: ", &n);

	int sum = n * (n + 1) / 2;
	printf("The sum 1 + 2 + ... + n is %d\n", sum);

	return 0;
}
