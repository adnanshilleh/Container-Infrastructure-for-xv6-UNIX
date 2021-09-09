CM_Report

Level 0: Implement the logic to send to the CM the container specification. Parse and print out the configuration correctly.
Usage:
```
char* specs[3];
parse_specs(specs)
```
Returns 0 on success and populates string param string array.
Returns -1 on error.
Uses jsmn library to parse specified .json file
Checks to ensure only "init", "fs", and "nproc" are specified
    Assumption: You must provide specifications for these tokens and the token names must match exactly

Level 1: Process launched into new directory and uses of ../ are prevented