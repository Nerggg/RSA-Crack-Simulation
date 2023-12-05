#ifndef DINLIST_H
#define DINLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct dinList {
  long long int size;
  long long int* list;
} dinList;

void append(dinList *arr, long long int value);

#endif