/*
 *	Module 4: Scheduling
 *	Level 0: Implement the system call, and set the processes priority.
 */


#include "types.h"
#include "user.h"

int
main()
{
	printf(1, "\nMODULE 4 LEVEL 0 STARTING\n");

	int priority = 10;
	int status = prio_set(getpid(), priority);
	printf(1, "\nSETTING PRIORITY TO %d...%s\n", priority, status == 0 ? "PASSED" : "FAILED");

	exit();

	return 0;
}
