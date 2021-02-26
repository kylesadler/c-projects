#include "util.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
	int input;
	int sum = 0;
	bool inputPositive = true;
	printf("This program computes the sum of positive integers. Enter a negative integer to end the program.\n");
	while(inputPositive) {
		getIntFromUser("Enter an integer: ", &input);
		inputPositive = (input > 0);
		sum += input;
	}
	printf("The sum is %d!\n", sum);
	return 0;
}
