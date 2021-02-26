
#include <string.h>
#include <stdio.h>
#include <math.h>

int getIntFromUser(char *message, int *location) {
printf("%s", message);
scanf("%d", location);
}


void findRoots(int a, int b, int c) {
	printf("%d %d %d", a,b,c);
	printf();
	double discriminant = pow(b, 2) - 4*a*c;
	printf("%ld", discriminant);
	printf("\nThe roots are \n");
}

int main() {

int a,b,c;

getIntFromUser("Enter the value for a: ", &a);
getIntFromUser("Enter the value for b: ", &b);
getIntFromUser("Enter the value for c: ", &c);
findRoots(a,b,c);
}
