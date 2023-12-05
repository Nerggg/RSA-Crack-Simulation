#define boolean unsigned char
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct dinList {
  long long int size;
  long long int* list;
} dinList;

void append(dinList *arr, long long int value){
  long long int *new_ptr = realloc(arr->list, sizeof *(arr->list) * (arr->size + 1u));
  if (new_ptr == NULL) {
    fprintf(stderr, "Out of memory\n");
    exit (EXIT_FAILURE);
  }
  arr->list = new_ptr;
  arr->list[arr->size] = value;
  arr->size++;
}

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

int coprime(int num1, int num2) {  
    int min, count;
    boolean flag = true;  
    min = num1 < num2 ? num1 : num2;  
    for(count = 2; count <= min; count++) {  
        if( num1 % count == 0 && num2 % count == 0 ) {  
            flag = false;  
            break;  
        }  
    }  
    return(flag);  
} 
 
int gcdExtended(int a, int b, int* x, int* y) { 
    if (a == 0) { 
        *x = 0, *y = 1; 
        return b; 
    } 
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1); 
    *x = y1 - (b / a) * x1; 
    *y = x1; 
    return gcd; 
}

long long int modInverse(int A, int M) { 
    int x, y; 
    gcdExtended(A, M, &x, &y); 
    long long int res = (long long int) ((x % M + M) % M); 
    return res;
}  

int main() {
    FILE *fptr;
    dinList primes;
    primes.list = malloc(sizeof(long long int));
    primes.size = 0;
    char ch;
    int temp = 0;
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
    int p = primes.list[rand() % primes.size];
    int q = primes.list[rand() % primes.size];
    long long int n = (long long int) (p * q);
    long long int m = (long long int) ((p - 1) * (q - 1));

    dinList e;
    e.list = malloc(sizeof(long long int));
    e.size = 0;
    for (int i = 2; i < m; i++) {
        if (coprime(i, m)) {
            append(&e, i);
        }
    }

    long long int publicKey = e.list[rand() % e.size];

    long long int privateKey = modInverse(publicKey, m);

    printf("These are the random generated RSA components\n");
    printf("p: %d\n", p);
    printf("q: %d\n", q);
    printf("n: %lld\n", n);
    printf("m: %lld\n", m);
    printf("Public Key: %lld\n", publicKey);
    printf("Private Key: %lld\n\n", privateKey);

    printf("Now the code will begin to brute force the encryption only using the \'n\' value and the public key\n");
    printf("Please wait\n\n");

    boolean found = false;
    int i = 0, j;
    long long int privateKeyGuess;

    clock_t start = clock();
    while (i < primes.size && !found) {
        j = 0;
        while (j < primes.size && !found) {
            if ((long long int) (primes.list[i] * primes.list[j]) == n) {
                long long int mGuess = (long long int) ((primes.list[i] - 1) * (primes.list[j] - 1));
                for (int k = 0; k < mGuess; k++) {
                    if (k == publicKey) {
                        found = true;
                        privateKeyGuess = modInverse(k, mGuess);
                        break;
                    }
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
