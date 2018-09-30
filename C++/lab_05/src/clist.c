#include "clist.h"

void init_list(intrusive_list *list) {
    intrusive_node *head = &list->head;
    head->next = head;
    head->prev = head;
}

void add_node(intrusive_list *list, intrusive_node *node) {
    intrusive_node *last = list->head.prev;
    intrusive_node *head = &list->head;

    node->next = head;
    node->prev = last;

    head->prev = node;
    last->next = node;
}

void apply(intrusive_list *lst, void (*action)(void*, void*), void *s)
{
	intrusive_node *head = &lst->head;
    intrusive_node *node = head->next;

    for (; node != head; node = node->next)
	{
		action(s, node);
	}
}
// contract: node != &list->head
void remove_node(intrusive_list *list, intrusive_node *node) {
    intrusive_node *prev = node->prev;
    intrusive_node *next = node->next;

    prev->next = next;
    next->prev = prev;
}

int get_length(intrusive_list *list) {
    int length = 0;
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    for (; node != head; node = node->next)
        ++length;

    return length;
}
