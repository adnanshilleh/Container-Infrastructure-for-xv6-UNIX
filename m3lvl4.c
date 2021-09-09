/*
 *	Module 3: Synchronization
 *	Level 4: Implement your mutexes in a manner where if a critical 
 *	section is not owned by another thread, and  a thread is attempting 
 *	to lock it, it will avoid making a system call similar to futexes 
 *	as spelled out above.
 */


#include "types.h"
#include "user.h"

void
create_critical_section(int mux, int pid)
{
	printf(1, "\nPID %d READY\n", pid);
	mutex_lock(mux);

	printf(1, "\nPID %d ENTERED\n", pid);
	sleep(100);

	printf(1, "\nPID %d EXITING\n", pid);
	mutex_unlock(mux);
}

int
main()
{
	printf(1, "\nMODULE 3 LEVEL 4 STARTING\n");

	int mux;
	mux = mutex_create("MODULE");

	printf(1, "\nMUTEX CREATED WITH ID %d", mux);

	int pid = fork();
	int pid2 = fork();

	if (pid == 0)
		create_critical_section(mux, pid);
	else
	{
		int pid2 = fork();

		if (pid2 == 0){
			create_critical_section(mux, pid);
		}
		else{
			create_critical_section(mux, pid2);
		}

		wait();
	}

	if(pid2 == 0)
	{
		create_critical_section(mux, pid);
	}
	else{
		create_critical_section(mux, pid2);
		wait();
		wait();
	}

	printf(1, "\n\n");

	exit();
	return 0;
}