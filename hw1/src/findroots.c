#include <stdio.h>
#include <math.h>
#include "util.h"


void printRoots(int a, int b, int c) {

	if (a == 0) {
		printf("Not a valid second degree polynomial. Exiting...\n");
		return;
	}

	double discriminant = pow(b, 2) - 4*a*c;
	double aTimes2 = a*2;
	double discriminantSqrt = 0;
	printf("The discriminant is %.4f.\n", discriminant);

	if (discriminant != 0) {
		discriminantSqrt = sqrt(fabs(discriminant));
	}

	if (discriminant < 0) {
		double real = -b/aTimes2;
		double imaginary = discriminantSqrt / aTimes2;
		printf("The roots are %.4f + %.4fi and %.4f + %.4fi\n", real, imaginary, real, -imaginary);

	} else {
		double x1 = (-b + discriminantSqrt) / aTimes2;
		double x2 = (-b - discriminantSqrt) / aTimes2;
		printf("The roots are %.4f and %.4f\n", x1, x2);

	}

}

int main() {
	printf("This program finds the roots of second degree polynomials of the form ax^2 + bx + c.\n");

	int a,b,c;
	getIntFromUser("Enter the value for a: ", &a);
	getIntFromUser("Enter the value for b: ", &b);
	getIntFromUser("Enter the value for c: ", &c);

	printRoots(a, b, c);

}
