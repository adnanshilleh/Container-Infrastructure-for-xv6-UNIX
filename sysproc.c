#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "synch.h"

int
sys_fork(void)
{
	return fork();
}

int
sys_exit(void)
{
	exit();
	return 0; // not reached
}

int
sys_wait(void)
{
	return wait();
}

int
sys_kill(void)
{
	int pid;

	if (argint(0, &pid) < 0) return -1;
	return kill(pid);
}

int
sys_getpid(void)
{
	return myproc()->pid;
}

int
sys_sbrk(void)
{
	int addr;
	int n;

	if (argint(0, &n) < 0) return -1;
	addr = myproc()->sz;
	if (growproc(n) < 0) return -1;
	return addr;
}

int
sys_sleep(void)
{
	int  n;
	uint ticks0;

	if (argint(0, &n) < 0) return -1;
	acquire(&tickslock);
	ticks0 = ticks;
	while (ticks - ticks0 < n) {
		if (myproc()->killed) {
			release(&tickslock);
			return -1;
		}
		sleep(&ticks, &tickslock);
	}
	release(&tickslock);
	return 0;
}

int
sys_uptime(void)
{
	uint xticks;

	acquire(&tickslock);
	xticks = ticks;
	release(&tickslock);
	return xticks;
}

int
sys_mutex_create(void)
{
	char *name;

	if (argptr(0, (void*)&name, sizeof(*name) < 0)) return -1;

	return mutex_create(name);
}

int
sys_mutex_delete(void)
{
	int muxid;

	if (argint(0, &muxid) < 0) return -1;
	mutex_delete(muxid);

	return 0;
}

int
sys_mutex_lock(void)
{
	int muxid;
	struct mutex* mux;
	struct proc* p;

	p = myproc();
	
	if (argint(0, &muxid) < 0) return -1;

	//Add ability to test standard mutex
	if (FUTEX_ACTIVE)
	{
		mux = &mutex_table.max_muxarr[muxid];

		//Check if futex is locked
		if (mux->thread == -1)
		{
			xchg(&mux->thread, p->pid);
			xchg(&p->curr_mux_held[muxid], 1);
		}

		xchg(&mux->inuse, mux->inuse + 1);
		futex(mux);
		xchg(&mux->inuse, mux->inuse - 1);
		
	}
	else
		mutex_lock(muxid);

	return 0;
}

int
sys_mutex_unlock(void)
{
	int muxid;
	struct mutex * mux;
	struct proc *p;

	p = myproc();

	//Check that the muxid has been initialized and that
	//max number of mutexes allowed is not surpassed
	if (argint(0, &muxid) < 0 || muxid >= MUX_MAXNUM) return -1;

	if (FUTEX_ACTIVE)
	{
		mux = &mutex_table.max_muxarr[muxid];
		if (mux->thread != p->pid || p->curr_mux_held[muxid] != 1)
		{
			panic("WRONG THREAD, UNLOCK MUTEX");
		}

		xchg(&mux->thread, -1);
		xchg(&p->curr_mux_held[muxid], -1);

		if (mux->inuse > 0) cv_signal(muxid);
	}
	else mutex_unlock(muxid);

	return 0;
}

int
sys_cv_wait(void)
{
	int muxid;

	if (argint(0, &muxid) < 0) return -1;
	cv_wait(muxid);
	
	return 0;
}

int
sys_cv_signal(void)
{
	int muxid;

	if (argint(0, &muxid) < 0) return -1;
	cv_signal(muxid);
	
	return 0;
}

int
sys_prio_set(void)
{
	int pid;
	int priority;

	if (argint(0, &pid) < 0 || argint(1, &priority) < 0) return -1;

	return prio_set(pid, priority);
}

// This function sets the process's fakeroot flag to 1 and
// sets its fake root path to the path specified by spec.json

// TODO: Doesn't work because I couldn't get processes to properly inherit
// their parent's fakeroot properties. The original process does get their fake root set though.
int
sys_setroot(char* root)
{
	argptr(0, (void*)&root, sizeof(*root));

	// Once directory path is recieved, use it to set up the root for a container
	struct proc *p = 0;
	p = myproc();
	if (p == 0) return -1;

	p->frootpath = root;
	p->fakeroot = 1;
	
	return 1;
}

extern char * shm_get(char *);
char * sys_shm_get(char *name){
	char * nam;
	argptr(0, &nam, sizeof(name));
	return shm_get(nam);
}

extern int shm_rem(char *);
int sys_shm_rem(char *name){
	char * nam;
	argptr(0, &nam, sizeof(name));
	return shm_rem(nam);
}
