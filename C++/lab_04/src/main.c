#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int Compare_Int(void *a, void *b)
{ 
    int *int1 = a;
    int *int2 = b;
    return (*int1 > *int2);
}

int Compare_Char(void *a, void *b)
{
    char *chr1 = a;
    char *chr2 = b;
    return (*chr1 > *chr2);
}

int Compare_Str(void *a, void *b)
{
    char **str1 = a;
    char **str2 = b;
    return strcmp(*str1, *str2);
}

int main(int argc, char *argv[])
{
	if (strcmp(argv[1], "int") == 0)
	{
		int nums[argc];
		int i = 0;
		while (i + 2 < argc)
		{
			nums[i] = atoi(argv[i + 2]);
			i++;
		}
		merge_sort(nums, argc - 2, sizeof(int), Compare_Int);

    	i = 0; 
		while(i + 2 < argc)
		{
			printf("%i ", nums[i]); 
			i++;
		}
	} 
	else if (strcmp(argv[1], "str") == 0)
	{
		char *words[argc];
		int i = 0;
		while (i + 2 < argc)
		{
			words[i] = argv[i + 2];
			i++;
		}
		merge_sort(words, argc - 2, sizeof(char*), Compare_Str);

    	i = 0; 
		while(i + 2 < argc)
		{
			printf("%s ", words[i]); 
			i++;
		}
	} 
	else if (strcmp(argv[1], "char") == 0)
	{
		char letters[argc];
		int i = 0;
		while (i + 2 < argc)
		{
			letters[i] = *argv[i + 2];
			i++;
		}
		merge_sort(letters, argc - 2, sizeof(char), Compare_Char);
    	i = 0; 
		while(i + 2 < argc)
		{
			printf("%c ", letters[i]); 
			i++;
		} 
	}
	return 0;
}
