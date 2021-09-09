#include "container_manager.h"


int main()
{
    printf(1, "Hello world!\n");
    // Try to access stuff from root
    int fd;
    fd = open("../container_spec.json", O_RDONLY);
    if (fd > -1)
        printf(1, "Failed to prevent accesss of root: %d\n", fd);
    close(fd);
    exit();
}