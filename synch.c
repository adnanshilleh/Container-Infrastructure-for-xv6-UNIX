#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "synch.h"

void
mutex_init(void)
{
	initlock(&mutex_table.lock, "MUTEX TABLE LOCK");

	for (int i = 0; i < MUX_MAXNUM; i++)
	{
		mutex_table.max_muxarr[i].index =  i;
		mutex_table.max_muxarr[i].thread = -1;
		mutex_table.max_muxarr[i].assert = 0;
		mutex_table.max_muxarr[i].inuse = 0;
	}
	mutex_table.activemux = 0;
}

int
mutex_create(char *name)
{
    int i;

	acquire(&mutex_table.lock);
	if (mutex_table.activemux >= MUX_MAXNUM)
	{
		release(&mutex_table.lock);
		return -1;
	}

	xchg(&mutex_table.activemux, mutex_table.activemux + 1);

	for (i = 0; i < MUX_MAXNUM; i++)
	{
		if (mutex_table.max_muxarr[i].assert == 0)
		{
			initlock(&mutex_table.max_muxarr[i].lock, "MUTEX LOCKED");
			strncpy(mutex_table.max_muxarr[i].name, name, 0);
			mutex_table.max_muxarr[i].assert = 1;
			mutex_table.max_muxarr[i].thread = -1;
			mutex_table.max_muxarr[i].inuse = 0;
			break;
		}
	}
	release(&mutex_table.lock);
	return i;
}

void
mutex_delete(int muxid)
{
	struct mutex* mux;
	mux = &mutex_table.max_muxarr[muxid];

	if (mux->thread == -1 || mux->inuse > 0 || mux->assert == 0) return;

	acquire(&mutex_table.lock);

	mux->assert = 0;
	xchg(&mutex_table.activemux, mutex_table.activemux - 1);

	release(&mutex_table.lock);

	return;
}

void
mutex_lock(int muxid)
{
	struct mutex* mux;
	struct proc* currproc;

	currproc = myproc();
	mux = &mutex_table.max_muxarr[muxid];

	acquire(&mux->lock);

	while (mux->thread != -1) cv_wait(muxid);

	xchg(&mux->thread, currproc->pid);
	xchg(&currproc->curr_mux_held[muxid], 1);

	release(&mux->lock);
}

void
mutex_unlock(int muxid)
{
	struct mutex* mux;
	struct proc* currproc;

	currproc = myproc();		
	mux = &mutex_table.max_muxarr[muxid];

	if (mux->thread != currproc->pid || currproc->curr_mux_held[muxid] != 1)
	{
		panic("WRONG THREAD, UNLOCK MUTEX");
	}

	acquire(&mux->lock);

	xchg(&mux->thread, -1);

	currproc->mux_tracker = -1;
	xchg(&currproc->curr_mux_held[muxid], -1);
	cv_signal(muxid);

	release(&mux->lock);
}