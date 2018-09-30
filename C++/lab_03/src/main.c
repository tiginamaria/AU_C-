#include <string.h>
#include "clist.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct position_node 
{
	int x, y;
	struct intrusive_node node;
};

void remove_position(struct intrusive_list *ilist, int x, int y) 
{ 
	struct position_node *inode;
	struct intrusive_node *walknode = ilist->head, *to_del;
	while (walknode)
	{
		inode = container_of(walknode, struct position_node, node);
		to_del = walknode;
		walknode = walknode->next;
		if (inode->x == x && inode->y == y)
		{
			remove_node(ilist, to_del);
			free(inode);
		}			
	}
}

void add_position(struct intrusive_list *ilist, int x, int y) 
{
	struct position_node *inode = malloc(sizeof(struct position_node));
	inode->x = x;
	inode->y = y;
	add_node(ilist, &(inode->node));
}

void show_all_positions(struct intrusive_list *ilist) 
{
	struct position_node *inode;
	struct intrusive_node *walknode = ilist->head;
	while (walknode)
	{
		inode = container_of(walknode, struct position_node, node);
		int x = inode->x;
		int y = inode->y;
		printf ("(%i, %i) ", x, y);
		walknode = walknode->next;
	}
	printf("\n");
}

void remove_all_positions(struct intrusive_list *ilist) 
{
	struct position_node *inode;
	struct intrusive_node *walknode = ilist->head, *to_del;
	while (walknode)
	{
		inode = container_of(walknode, struct position_node, node);
		to_del = walknode;
		walknode = walknode->next;
		remove_node(ilist, to_del);
		free(inode);			
	}
}

int main() {

	struct intrusive_list l;
	init_list(&l);
	char s[10];
	int a, b;
	scanf("%s", s);
	while (strcmp(s,"exit"))
	{
		if (strcmp(s,"add") == 0)
		{
			scanf("%i %i", &a, &b);
			add_position(&l, a, b);
		}
		else if (strcmp(s,"rma") == 0)
		{
			remove_all_positions(&l);
		}
		else if (strcmp(s,"print") == 0)
		{
			show_all_positions(&l);
		}
		else if (strcmp(s,"len") == 0)
		{
			printf("%i \n", get_length(&l));
		}
		else if (strcmp(s,"rm") == 0)
		{
			scanf("%i %i", &a, &b);
			remove_position(&l, a, b);
		}
		else
		{
			printf("%s \n", "Unknown command");
		}
		scanf("%s", s);
	}
	remove_all_positions(&l);
     	return 0;
  
}
