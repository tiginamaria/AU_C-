#include "mergesort.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *Copy_Memory(char *dest, char *src, size_t n)
{
    char *ch = dest;
    while (n--)
    {
        *ch++ = *src++;
    }
    return  dest;
}

void merge(void *base, size_t num, size_t size, size_t s, int (*compar)(void*, void*))
{
    size_t split = s * size;
    char *first = malloc(split);
    char *p1 = Copy_Memory(first, base, split);
    char *array = base;
    char *p2 = array + split;
    size_t i = 0;
    size_t j = s;
    while (i < s)
    {
        if (j == num || compar(p1, p2) <= 0)
        {
            size_t k = 0;
            while (k < size)
            {
                *array++ = *p1++;
                k++;
            }
            i++;
        }
        else
        {
            size_t k = 0;
            while (k < size)
            {
                *array++ = *p2++;
                k++;
            }
            j++;
        }
    }
    free(first);
}

void merge_sort(void *base, size_t num, size_t s, int (*compar)(void*, void*))
{
    if (num > 1)
    {
        size_t m = (num + 1) / 2;
        merge_sort(base, m, s, compar);
        merge_sort(base + m * s, num - m, s, compar);
        merge(base, num, s, m, compar);
    }
}
