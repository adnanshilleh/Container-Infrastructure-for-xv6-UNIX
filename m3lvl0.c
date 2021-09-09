/*
 *	Module 3: Synchronization
 *	Level 0: Implement the system calls to allocate and free mutexes, 
 *	along with the kernel data-structures to track the mutexes.
 */


#include "types.h"
#include "user.h"

int
main()
{
	int mux;

	printf(1, "\nMODULE 3 LEVEL 0 STARTING\n");

	mux = mutex_create("MODULE");
	mutex_lock(mux);
	mutex_unlock(mux);
	mutex_delete(mux);

	exit();

	return 0;
}