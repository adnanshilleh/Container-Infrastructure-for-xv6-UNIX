/*
 *	Module 3: Synchronization
 *	Level 3: Handle the case where a process terminates accidently (faults).  
 *	Release any mutexes it holds, and ensure that it is no longer blocked on conditions.
 */


#include "types.h"
#include "user.h"

int
main()
{
	printf(1, "\n\nMODULE 3 LEVEL 3 STARTING\n\n");
	printf(1, "\nNOTE: PURPOSE OF TEST IS TO EXIT.");

	int mux;
	int mux2;

	mux = mutex_create("MODULE TEST");
	mux2 = mutex_create("MODULE TEST");

	mutex_lock(mux);
	mutex_lock(mux2);

	printf(1, "\n\nHOLDING MUTEX: %d\n\n", mux);
	printf(1, "\n\nHOLDING MUTEX: %d\n\n", mux2);

	return 0;
}