#ifndef _MERGESORT_H_
#define _MERGESORT_H_
#include <stddef.h>
void merge_sort(void *base, size_t num, size_t s, int (*compar)(void*, void*));
#endif
