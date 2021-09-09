#ifndef LIST_H
#define LIST_H


//Stack based linked list from homework 1, modiefied

struct linked_list
{
	struct node* head;
	struct node* tail;
	uint len; 				//length
};

struct node
{
	struct node *next;
	struct node *prev;
	void *value;
};

void ll_init(struct linked_list* new_list);
void ll_add(struct linked_list* ll, void* value, struct node* new_node);
struct node* ll_remove_first(struct linked_list* ll);
int ll_length(struct linked_list* ll);

#endif