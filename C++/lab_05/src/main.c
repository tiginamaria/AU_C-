#include "position.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "clist.h"
#include <string.h>

void save_bin (void *file,  void *dot)
{
	FILE *f = file;
	struct intrusive_node *node = dot;	
	position_node *pnode = container_of(node, position_node, node);
    fwrite(&(pnode->x), 3, 1, f);
	fwrite(&(pnode->y), 3, 1, f);
}

void save_text (void *file,  void *dot)
{
	FILE *f = file;
	struct intrusive_node *node = dot;	
	position_node *pnode = container_of(node, position_node, node);
    fprintf(f, "%d %d \n", pnode->x, pnode->y);
}

void print (void *s, void *dot)
{
	char *str = s;
	struct intrusive_node *node = dot;
    position_node *pnode = container_of(node, position_node, node);
    printf(str, pnode->x, pnode->y);
}

void count (void *counter, void *_)
{
	int *k = counter;
	(*k)++;
}

int main(int argc, char *argv[]) {
    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);
	int x, y, counter = 0;
	if (strcmp(argv[1], "loadtext") == 0)
	{	
		FILE *f = fopen (argv[2], "rt");
		while(fscanf(f, "%d %d", &x, &y) == 2)
		{
			add_position(l, x, y);
		}
		fclose(f);
	}
	else if(strcmp(argv[1], "loadbin") == 0)
	{
		FILE *f = fopen (argv[2], "rb");
		x = 0; 
		while(fread(&x, 3, 1, f))
		{
			y = 0;
			fread(&y, 3, 1, f);
			add_position(l, x, y);
			x = 0; 
		}
		fclose(f);
	}
	if (strcmp(argv[3], "print") == 0)
	{
		apply(l, print, argv[4]);
	}
	else if (strcmp(argv[3], "count") == 0)
	{
		apply(l, count, &counter);
		printf("%d", counter);
	}
	else if (strcmp(argv[3], "savetext") == 0)
	{
		FILE *f = fopen (argv[4], "wt");
		apply(l, save_text, f);
		fclose(f);
	}
	else if (strcmp(argv[3], "savebin") == 0)
	{
		FILE *f = fopen (argv[4], "wb");
		apply(l, save_bin, f);
		fclose(f);
	}
    
    remove_all(l);

    return 0;
}
