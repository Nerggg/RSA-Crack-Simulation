#define boolean unsigned char
#define true 1
#define false 0

#include <stdio.h>
#include <math.h>

int main() {
    int maxPrime, primeCount = 0;
    boolean prime;

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
            primeCount++;
        }   
    }

    int primes[primeCount];
    int idxTemp = 0;
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
            primes[idxTemp] = i;
            idxTemp++;
        }
    }

    FILE *fptr;
    fptr = fopen("prime.txt", "w");
    for (int i = 0; i < primeCount; i++) {
        fprintf(fptr, "%d ", primes[i]);
    }
    fclose(fptr);
}