//Priority queue that runs in O(1) for module 4, modified from HW2

#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"
#include "list.h"
#include "proc.h"
#include "pqueue.h"

void pq1_init(void)
{
	//Create priority queue
	uint i;
	pqueue.size = 0;

	//Populate priority queue with linked lists that each represent a priority
	for (i = PRIO_MIN; i < PRIO_MAX + 1; i++)
	{
		ll_init(&pqueue.queue[i]);
		pqueue.queue[i].head = 0;
		pqueue.queue[i].tail = 0;
		pqueue.queue[i].len = 0;
	}

	for (i = 0; i < NPROC; i++) freelist_add(&pqueue.nodes[i]);

	initlock(&pqueue.lock, "PRIORITY QUEUE LOCK");
}

void enqueue(struct proc * p)
{
	int priority;
	priority = p->priority;

	if (priority > PRIO_MAX + 1) return;

	acquire(&pqueue.lock);
	pqueue.size += 1;
	pq1_add(&pqueue.queue[priority], p);
	release(&pqueue.lock);
}

struct proc* dequeue()
{
	if (pqueue.size == 0) return 0;

	uint i;

	acquire(&pqueue.lock);
	for (i = PRIO_MIN; i < PRIO_MAX + 1; i++)
		if (ll_length(&pqueue.queue[i]) > 0)
		{
			pqueue.size -= 1;
			
			struct proc *p;
			p = pq1_remove(&pqueue.queue[i]);

			return p;
		}
	release(&pqueue.lock);
	return 0;
}

void
pq1_add(struct linked_list* ll, void* value)
{
	struct node* new_node;
	new_node = freelist_remove();

	ll_add(ll, value, new_node);
}

struct proc *
pq1_remove(struct linked_list* ll)
{
	struct node* new_node; 
	new_node = ll_remove_first(ll);

	struct proc* p;
	p = (struct proc *)(new_node->value);

	freelist_add(new_node);
	release(&pqueue.lock);

	return p;
}

void
freelist_add(struct node* new_node)
{
	ll_add(&pqueue.freelist, 0, new_node);
}

struct node*
freelist_remove()
{
	struct linked_list* ll;
	ll = &pqueue.freelist;

	if (ll_length(ll) == 0) panic("FREELIST EMPTY");

	return ll_remove_first(ll);
}