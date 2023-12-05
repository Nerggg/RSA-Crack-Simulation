#define boolean unsigned char
#define true 1
#define false 0

#include <stdio.h>
#include <math.h>
#include "dinlist.h"

int main() {
    int maxPrime;
    boolean prime;
    dinList primes;
    primes.list = malloc(sizeof(unsigned long long int));
    primes.size = 0;

    printf("Enter the prime number bit size: ");
    scanf("%d", &maxPrime);
    maxPrime = pow(maxPrime, 2);

    for (int i = 2; i < maxPrime; i++) {
        prime = true;
        if (i > 2) {
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    prime = false;
                    break;
                }
            }
        }
        if (prime) {
            append(&primes, i);
        }   
    }

    FILE *fptr;
    fptr = fopen("prime.txt", "w");
    for (int i = 0; i < primes.size; i++) {
        fprintf(fptr, "%lld ", primes.list[i]);
    }
    fclose(fptr);
}
