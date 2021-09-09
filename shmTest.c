#include "types.h"
#include "stat.h"
#include "user.h"

//JAKE's SHM TESTING

int main(){
    uint region = (uint)shm_get("test1");
    printf(1, "%d\n", region);

    printf(1, "%d\n", (uint)shm_rem("test1"));
    
    uint region2 = (uint)shm_get("test2");
    printf(1, "%d\n", region2);

    region = (uint)shm_get("test1");
    printf(1, "%d\n", region);

    uint region3 = (uint)shm_get("test2");
    printf(1, "%d\n", region3);

    exit();
}