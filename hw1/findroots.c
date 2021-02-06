
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "util.h"


void findRoots(int a, int b, int c, char *roots) {
	double discriminant = pow(b, 2) - 4*a*c;
	double discriminantSqrt = 0;
	printf("The discriminant is %.4f.", discriminant);

	if (discriminant != 0) {
		discriminantSqrt = sqrt(fabs(discriminant));
	}

	if (discriminant < 0) {
		double real = (double)-b/2*a;
		double imaginary = discriminantSqrt / 2*a;
		sprintf(roots, "%.4f + %.4fi and %.4f + %.4fi", real, imaginary, real, -imaginary);

	} else {
		double x1 = (-b + discriminantSqrt) / 2*a;
		double x2 = (-b - discriminantSqrt) / 2*a;
		sprintf(roots, "%.4f and %.4f", x1, x2);

	}

}

int main() {
	printf("This program finds the roots of second degree polynomials of the form ax^2 + bx + c.\n");

	int a,b,c;
	getIntFromUser("Enter the value for a: ", &a);
	getIntFromUser("Enter the value for b: ", &b);
	getIntFromUser("Enter the value for c: ", &c);

	char roots[100];
	findRoots(a, b, c, roots);
	printf("\nThe roots are %s.\n", roots);

}
