
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "util.h"

bool isPrime(int n){
    if (n < 2) { // 1 is not prime!
        return false;
    }
    
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void printPrimes(int start, int end) {
    for (int i = start; i <= end; i++){
        if (isPrime(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {

    printf("This program finds the positive prime numbers between two integers.\n");

	int start, end;
	getIntFromUser("Enter the first integer: ", &start);
	getIntFromUser("Enter the second integer: ", &end);

    printf("Primes between %d and %d:\n", start, end);
	printPrimes(start, end);

}
