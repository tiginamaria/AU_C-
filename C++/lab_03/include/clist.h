#ifndef _CLIST_H_
#define _CLIST_H_
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))
struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
};

struct intrusive_list {
  struct intrusive_node* head;
};

void init_list(struct intrusive_list *ilist);
void add_node(struct intrusive_list *ilist, struct intrusive_node *inode );
void remove_node(struct intrusive_list *ilist, struct intrusive_node *inode);
int get_length(struct intrusive_list *ilist );

#endif
