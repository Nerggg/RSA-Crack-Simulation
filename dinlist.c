#include "dinlist.h"

void append(dinList *arr, long long int value) {
  long long int *new_ptr = realloc(arr->list, sizeof *(arr->list) * (arr->size + 1u));
  if (new_ptr == NULL) {
    fprintf(stderr, "Out of memory\n");
    exit (EXIT_FAILURE);
  }
  arr->list = new_ptr;
  arr->list[arr->size] = value;
  arr->size++;
}