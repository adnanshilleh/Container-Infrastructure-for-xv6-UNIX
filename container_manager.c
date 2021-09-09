#include "container_manager.h"

int main()
{
    // Test the .json file is parsed correctly    
    char* specs[3];
    if (parse_specs(specs) != 0)
    {
        printf(stdout, "parse unsuccessful\n");
        exit();
    }

    printf(stdout, "CM creating container with init = %s, root fs = %s, and max num processes = %s\n", specs[0], specs[1], specs[2]);
    
    // Test the root is set correctly for container
    if (setup_root(specs[0], specs[1]) == -1)
    {
        printf(stdout, "Setup root unsuccessful\n");
        exit();
    }
    exit();
}  