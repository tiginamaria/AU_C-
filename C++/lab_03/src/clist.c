#include "clist.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void init_list( struct intrusive_list *ilist)
{
	ilist->head = NULL;
}

void add_node(struct intrusive_list *ilist, struct intrusive_node *inode)
{
	if  (ilist->head == NULL)
	{
		inode->prev = NULL;
		inode->next = NULL;
	}
	else
	{
		inode->next = ilist->head;
		inode->prev = NULL;
		ilist->head->prev = inode;	
	}
	ilist->head = inode;
}
void remove_node(struct intrusive_list *ilist, struct intrusive_node *inode)
{
	if (inode->prev)
	{
		inode->prev->next = inode->next;
	}
	if (inode->next) 
	{
		inode->next->prev = inode->prev;
	}
	if (ilist->head == inode)
	{
		if (ilist->head->next)
		{
			ilist->head = ilist->head->next;
		}
		else
		{
			ilist->head = NULL;
		}
	}			
}	

int get_length(struct intrusive_list *ilist )
{
	struct intrusive_node *inode = ilist->head;
	int k = 0;
	while (inode)
	{
		inode = inode->next;
		k++;
	}
	return k;
}


