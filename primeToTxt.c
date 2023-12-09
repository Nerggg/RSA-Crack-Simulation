#define boolean unsigned char
#define true 1
#define false 0

#include <stdio.h>
#include <math.h>
#include "dinlist.h"

unsigned long long int power(unsigned long long int x, unsigned long long int y) {
    unsigned long long int temp;
    if (y == 0)
        return 1;
    temp = power(x, y / 2);
    if (y % 2 == 0)
        return temp * temp;
    else
        return x * temp * temp;
}

int main() {
    unsigned long long int maxPrime;
    boolean prime;
    dinList primes;
    primes.list = malloc(sizeof(unsigned long long int));
    primes.size = 0;

    printf("Enter the prime number bit size: ");
    scanf("%lld", &maxPrime);
    while (maxPrime >= 64) {
        printf("Please enter below 64 bit (it goes beyond C's capability)\n");
        printf("Enter the prime number bit size: ");
        scanf("%lld", &maxPrime);
    }
    maxPrime = power(2, maxPrime);

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
