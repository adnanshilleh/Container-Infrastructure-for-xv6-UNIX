# REPORT

## ADNAN SHILLEH

    Modules and levels achieved:
    Module 3:
        Level 0, 1, 2, 3, and 4 implemented
    Module 4:
        Level 0 achieved, level 1 implemented but does not work 100%

    Work done on Module 3:
        Adnan Shilleh
    Work done on Module 4:
        Adnan Shilleh

Documentation on how each level was evaluated:

MODULE 3
    ->Level 0: Implement the system calls to allocate and free mutexes, along with the kernel 
    data-structures to track the mutexes.
            Mutex system calls were created to block waiting for requests/responses. In
            accordance with the provided prototypes, SLEEPING and RUNNABLE were used through 
            cv_wait and cv_signal. In mutex_lock, I checked that the thread was being used 
            and then specified the mutex id that the condition variable is associated with. 
            Once mutex_unlock is called, cv_signal wakes up processes that are sleeping on 
            condition variable. Each system call was tested in m3lvl0 by calling create, lock,
            unlock, and delete.

    ->Level 1: Logic in the kernel to block processes locking a mutex that is already locked 
    (i.e. that has an already occupied critical section), and to wake up a thread blocked on 
    a mutex for the same reason.  Mutual exclusion is required.  This is very similar to the 
    previous homework.
            This level was tested in m3lvl1. In this test, a process attempts to access a critical
            section that is locked by the mutex. This test is designed so that one process is in the
            critical section while the other one is ready and waiting. Once the first process has exited
            the critical section, the second process will enter and then exit. This is displayed by the 
            output. Even if a process indicates that it is ready, it will not enter until the process 
            occupying the critical section has exited.

    ->Level 2: Implement condition variables that inter-operate properly with the mutexes from the 
    previous level.
            The logic of cv_wait and cv_signal are briefly discussed above. The line in cv_wait in proc.c
            currproc->condvar_blocked = muxid sets the condition variable to the muxid that is being waited 
            on. Once that is done, sleep() is called until cv_signal wakes the process with wakeup(). The for
            loop iterates through the ptable to check which process is currently sleeping based the condition
            variable

    ->Level 3: Handle the case where a process terminates accidently (faults).  Release any mutexes it holds, and ensure that it is no longer blocked on conditions.
            Global structure array cur_mux_held was created in proc.h under struct proc. This structure was created as recommended for
            keeping track of all the mutexes each process is holding. The test file m3lvl3 is meant to test this level and is purposefully
            returns trap 14 err 5 on cpu 1 eip 0xffffffff addr 0xffffffff--kill proc.

    ->Level 4: Implement your mutexes in a manner where if a critical section is not owned by another thread, and  a thread is attempting to lock it, it will avoid making a system call similar to futexes as spelled out above.
            The futex system call is executed when a lock is held. The test file m3lvl4 is meant to test this level. Compared to other tests
            the only difference with this one is that it calls several processes.

    
MODULE 4
    ->Level 0: Implement the system call, and set the processes priority.
            System call for prio_set was implemented in proc.c. To test level 0, I created a file called m4lvl0 where prio_set is called
            and a priority is set. If status is equal to zero, then the test passes.
    ->Level 1: Proper error checking for all edge cases for the system call
            An O(1) priority queue and a linked list based off of HW1 and HW2 were created. Instead of using a queue of queues, I used a 
            linked list instead. The file m4lvl1 is meant to test whether a process can change it's priority in which the test will fail
            if it tries to do so.


            
## Oscar Becerra: Worked on level 0 and 1

Worked on container manager. Completed level 0 and tested by changing specifications in container_specifications.json and monitoring 
whether the container manager's parser failed or not when it was supposed to. I made sure the parser exits the container manager if 
there are too many or too few parameter specifications or if the .json file could not be found/read.


Worked on and tested level 1. Tested that the container manager exists if the directory to launch the container in doesn't exist, if the
file to execute doesn't exist inside the specified container directory, or if the container could not fork a process into the container directory. 
Tested to make sure various programs could be launched if specified in the .json specs like helloworld.c and sh.c. Tested to make sure process was
 launched into the correct directory by calling /ls. Tested to make sure a program could not access the root through "cd .." or "/" or "../". I tried 
implementing this behavior by modifying namex in fs.c but ultimately could not get the appropriate behavior to work. I also tried a naive solution of 
parsing commands in shell to remove "/" and ".." to go under root but this only worked for sh.c and would disable accessing root for any process. 
Helloworld.c attempts to open a file in root when it is part of a container in /c1/. It fails since the open function is able to return a file descriptor. 
Tests were done in container_manager.c, helloworld.c, and interacting in sh launched in a container.

## Jake Harris || Shared Memory

shmTest.c goes through testing the two different functions of shm_get and shm_rem.

Level 0: System calls and kernel data-structure to track SHM_MAXNUM shared memory regions (tracking processes, and virtual memory addresses the regions are mapped into). Complete. Use SHM_GET(NAME) and SHM_REM(NAME) to access the address of a new shared memory region and then to remove that region.

Level 1: Implement the system calls to share memory between two processes, including mapping in the actual shared memory. Complete. Use SHM_GET(NAME) and SHM_REM(NAME) to access the address of a new shared memory region and then to remove that region.

Level 2: Maintain the shared memory region across forks of the process. In Progress.

Level 3: Thoroughly test that your shared memory region is properly maintained, or deallocated, depending on which processes fork, exit, and exec. This will require reference counting on the shared memory region, and you only deallocate the memory for it when all threads accessing it exit or unmap it. Complete.
