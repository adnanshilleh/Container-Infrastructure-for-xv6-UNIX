Jake Harris || Shared Memory

shmTest.c goes through testing the two different functions of shm_get and shm_rem.

Level 0: System calls and kernel data-structure to track SHM_MAXNUM shared memory regions (tracking processes, and virtual memory addresses the regions are mapped into).
    Complete. Use SHM_GET(NAME) and SHM_REM(NAME) to access the address of a new shared memory region and then to remove that region.

Level 1: Implement the system calls to share memory between two processes, including mapping in the actual shared memory.
    Complete. Use SHM_GET(NAME) and SHM_REM(NAME) to access the address of a new shared memory region and then to remove that region.

Level 2: Maintain the shared memory region across forks of the process.
    In Progress.

Level 3: Thoroughly test that your shared memory region is properly maintained, or deallocated, depending on which processes fork, exit, and exec.  This will require reference counting on the shared memory region, and you only deallocate the memory for it when all threads accessing it exit or unmap it.
    Complete.
