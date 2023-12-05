#define boolean unsigned char
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dinlist.h"

int ctoi(char letter) {
    if (letter == '0') {
        return 0;
    }
    else if (letter == '1') {
        return 1;
    }
    else if (letter == '2') {
        return 2;
    }
    else if (letter == '3') {
        return 3;
    }
    else if (letter == '4') {
        return 4;
    }
    else if (letter == '5') {
        return 5;
    }
    else if (letter == '6') {
        return 6;
    }
    else if (letter == '7') {
        return 7;
    }
    else if (letter == '8') {
        return 8;
    }
    else if (letter == '9') {
        return 9;
    }
}

unsigned long long int power(unsigned long long int x, unsigned long long int y)
{
    unsigned long long int temp;
    if (y == 0)
        return 1;
    temp = power(x, y / 2);
    if (y % 2 == 0)
        return temp * temp;
    else
        return x * temp * temp;
}

unsigned long long int gcdExtended(unsigned long long int a, unsigned long long int b, unsigned long long int* x, unsigned long long int* y) { 
    if (a == 0) { 
        *x = 0, *y = 1; 
        return b; 
    } 
    unsigned long long int x1, y1;
    unsigned long long int gcd = gcdExtended(b % a, a, &x1, &y1); 
    *x = y1 - (b / a) * x1; 
    *y = x1; 
    return gcd; 
}

unsigned long long int modInverse(unsigned long long int A, unsigned long long int M) { 
    unsigned long long int x, y; 
    gcdExtended(A, M, &x, &y); 
    unsigned long long int res = (unsigned long long int) ((x % M + M) % M); 
    return res;
}  

boolean coprime(unsigned long long int num1, unsigned long long int num2) {  
    unsigned long long int min, count;
    boolean flag = true;  
    min = num1 < num2 ? num1 : num2;  
    for(count = 2; count <= min; count++) {  
        if(num1 % count == 0 && num2 % count == 0) {  
            flag = false;  
            break;  
        }  
    }  
    return flag;  
} 

unsigned long long int find_coprime(unsigned long long int m) {
    for (unsigned long long int a = m/2 + 1; a > 2; a--) {
        if (coprime(a, m)) {
            return a;
        }
    }
}

int main() {
    FILE *fptr;
    dinList primes;
    primes.list = malloc(sizeof(unsigned long long int));
    primes.size = 0;
    char ch;
    unsigned long long int temp = 0;
    fptr = fopen("prime.txt", "r");
    do {
        ch = fgetc(fptr);
        if (ch != ' ') {
            temp = temp*10 + ctoi(ch);
        }
        else {
            append(&primes, temp);
            temp = 0;
        }
    } while (ch != EOF);
    fclose(fptr);

    srand(time(NULL));
    unsigned long long int p = primes.list[rand() % primes.size];
    unsigned long long int q = primes.list[rand() % primes.size];
    unsigned long long int n = (unsigned long long int) (p * q);
    unsigned long long int m = (unsigned long long int) ((p - 1) * (q - 1));

    printf("p: %lld\n", p);
    printf("q: %lld\n", q);
    printf("n: %lld\n", n);
    printf("m: %lld\n", m);
    printf("Now the code will generate a public key based on the value of \'m\'\n");
    printf("Please wait\n\n");

    unsigned long long int publicKey = find_coprime(m);

    unsigned long long int privateKey = modInverse(publicKey, m);

    printf("These are the random generated RSA components\n");
    printf("p: %lld\n", p);
    printf("q: %lld\n", q);
    printf("n: %lld\n", n);
    printf("m: %lld\n", m);
    printf("Public Key: %lld\n", publicKey);
    printf("Private Key: %lld\n\n", privateKey);

    printf("Now the code will begin to brute force the encryption only using the \'n\' value and the public key\n");
    printf("Please wait\n\n");

    boolean found = false;
    unsigned long long int i = 0, j;
    unsigned long long int privateKeyGuess;

    clock_t start = clock();
    while (i < primes.size && !found) {
        j = 0;
        while (j < primes.size && !found) {
            if ((unsigned long long int) (primes.list[i] * primes.list[j]) == n) {
                unsigned long long int mGuess = (unsigned long long int) ((primes.list[i] - 1) * (primes.list[j] - 1));
                if (find_coprime(mGuess) == publicKey) {
                    privateKeyGuess = modInverse(publicKey, mGuess);
                    found = true;
                }
            }
            j++;
        }
        i++;
    }
    clock_t stop = clock();
    double timeTaken = (double)(stop - start) / CLOCKS_PER_SEC;

    i--;
    j--;

    printf("Brute force completed!\n");
    printf("Time taken: %f\n", timeTaken);
    printf("Guessed p and q value: %lld and %lld\n", primes.list[i], primes.list[j]);
    printf("Guessed private key: %lld\n", privateKeyGuess);
}
