#include "defs.h"
#include "list.h"

#ifndef PQUEUE_H
#define PQUEUE_H

#define PRIO_MIN 0
#define PRIO_MAX 10

struct
{
	struct linked_list queue[PRIO_MAX + 1];
	struct node nodes[NPROC + 1];
	struct linked_list freelist;
	struct spinlock lock;
	uint size;
} pqueue;

void pq1_init(void);
void enqueue(struct proc* p);
struct proc* dequeue();
void freelist_add(struct node* new_node);
struct node* freelist_remove();
void pq1_add(struct linked_list* ll, void* value);
struct proc* pq1_remove(struct linked_list* ll);

#endif