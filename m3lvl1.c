/*
 *	Module 3: Synchronization
 *	Level 1: Logic in the kernel to block processes locking a mutex 
 *	that is already locked (i.e. that has an already occupied critical section), 
 *	and to wake up a thread blocked on a mutex for the same reason.  Mutual 
 *	exclusion is required.  This is very similar to the previous homework
 */


#include "types.h"
#include "user.h"

void
create_critical_section(int mux, int pid)
{
	printf(1, "\nPID %d READY/WAITING\n", pid);
	mutex_lock(mux);

	printf(1, "\nPID %d ENTERING\n", pid);
	sleep(100);

	printf(1, "\nPID %d EXITING\n", pid);
	mutex_unlock(mux);
}

int
main()
{
	printf(1, "\nMODULE 3 LEVEL 1 STARTING\n");

	int mux = mutex_create("module");
	printf(1, "\nMUTEX CREATED WITH ID %d", mux);

	int pid = fork();

	if (pid == 0)
		create_critical_section(mux, pid);
	else
	{
		sleep(50);
		create_critical_section(mux, pid);
		wait();
	}

	printf(1, "\n\n");

	exit();
	return 0;
}