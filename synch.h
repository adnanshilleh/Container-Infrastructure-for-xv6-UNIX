#include "spinlock.h"
#include "types.h"

#ifndef SYNCH_H
#define SYNCH_H

#define MUX_MAXNUM 32
#define FUTEX_ACTIVE 0

int mutexuse[MUX_MAXNUM];

struct mutex {
	uint index;				//index of mutex
    uint thread;			//Thread that is occupying mutex
	uint assert;			//Indicates that mutex has been asserted
    uint inuse;				//Mutex has been enabled
	char* name;			    //Mutex name
	struct spinlock lock;	//Protects mutex		
};

struct{
	uint activemux;
	struct mutex max_muxarr[MUX_MAXNUM];
	struct spinlock lock;
}mutex_table;

void mutex_init(void);
int  mutex_create(char *name);
void mutex_delete(int muxid);
void mutex_lock(int muxid);
void mutex_unlock(int muxid);

#endif