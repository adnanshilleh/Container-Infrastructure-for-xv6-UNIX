#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "list.h"
#include "pqueue.h"

//MODIFIED LINKED LIST FROM HOMEWORK 1 SINCE CANT USE MALLOC

void
ll_init(struct linked_list* new_list)
{
	//Initialize an empty linked list and set to 0
	new_list->len = 0;
	new_list->head = 0;
	new_list->tail = 0;
}


//Add node to the linked list, similar to implementation from HW1 but modified
void
ll_add(struct linked_list* ll, void* value, struct node* new_node)
{
	//If linked list is populated, add to the head of the list since it is stack based
	if (ll->len > 0)
		ll->head->prev = new_node;

	//If linked list is empty, add to the tail
	if (ll->tail == 0)
		ll->tail = new_node;

	//Reset pointers from linked list structs
	new_node->value = value;
	new_node->next = ll->head;
	new_node->prev = 0;
	ll->head = new_node;

	//Increase length in linked list
	ll->len = (ll->len) + 1;
}


//Removes the value at the head of a linked list and returns the value
struct node*
ll_remove_first(struct linked_list* ll)
{
	struct node* holder;

	holder = ll->head;
	ll -> head = holder -> next;
	ll->len = (ll->len) - 1;

	return holder;
}


//Returns the total number of values in the linked list
int
ll_length(struct linked_list* ll)
{
	return ll->len;
}