/*
 *	Module 4: Scheduling
 *	Level 1: Proper error checking for all edge cases for the system call.
 */

#include "types.h"
#include "user.h"

int
main()
{
	printf(1, "\nMODULE 4 LEVEL 1 STARTING\n");

	int priority = 10;

	printf(1, "\nTEST TO ENSURE PRIORITY CANNOT BE MADE A HIGHER PRIORITY\n");
	for (priority = 10; priority >= 0; priority--)
	{
		int status = prio_set(getpid(), priority);
		printf(1, "\nSETTING PRIORITY TO: %d...%s\n", priority, status == 0 ? "PASSED" : "FAILED");
	}

	printf(1, "ALL PRIORITY SETS (EXCEPT 5 AND ABOVE) SHOULD FAIL\n");

	exit();
	return 0;
}