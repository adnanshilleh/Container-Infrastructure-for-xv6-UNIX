#include "types.h"
#include "user.h"
#include "jsmn.h"
#include "fcntl.h"

#define O_RDONLY 0x000
#define stdout 1

int parse_specs(char** specs);
static int jsoneq(char*, jsmntok_t*, char*);

int setup_root(char* init, char* fakeRoot);
char *argv[] = {"sh", 0};

int
setup_root(char* init, char* fakeRoot)
{
    printf(1, "Container Manager starting...\n");
    printf(1, "CM awaiting requests...\n");
    // Parent
    int cpid = fork();
    if (cpid != 0)
    {
        for (;;)
        {
            wait();
            exit();
        }
    }
    // Child
    if (cpid == 0)
    {
        char* root = fakeRoot;
        if (testsetroot(root) == -1)
        {
            wait();
            exit();
        }
        
        int pid, wpid;


        if (open("console", O_RDWR) < 0) {
            mknod("console", 1, 1);
            open("console", O_RDWR);
        }
        dup(0); // stdout
        dup(0); // stderr

        
        pid = fork();
        if (pid < 0) {
            printf(1, "init: fork failed\n");
            exit();
        }
        
        if (pid == 0) {

            exec(init, argv); // specs: init: helloworld.c
            printf(1, "init: exec %s failed\n", init);
            exit();
        }
        while ((wpid = wait()) >= 0 && wpid != pid) printf(1, "zombie!\n");

        wait();
        exit();
    }
    
    return 1;
}

// Function from jsmn library that checks for token matches
static int 
jsoneq(char *json, jsmntok_t *tok, char *s) 
{
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

// Function that uses jsmn library to parse .json file
int
parse_specs(char** specs)
{
    // Get .json file into a string
    int fd;
    int size;
    char buffer[100];
    
    fd = open("container_spec.json", O_RDONLY); 
    if (fd < 0) return -1;
    
    size = read(fd, buffer, 100);
    if (size == -1) return -1;

    buffer[size] = '\0';

    // Using jsmn library to get tokens
    int i;
    int count;

    char *JSON_STRING = buffer;

    if (close(fd) < 0) return -1;

    // We should always expect 7 tokens. E.g: 1 object (always), init, /sh, fs, /c1/, nproc, 4
    jsmn_parser parser;
    jsmntok_t t[7];

    jsmn_init(&parser);

    count = jsmn_parse(&parser, buffer, strlen(buffer), t, 7);

    // The correct number of tokens after parsing must be 7
    if (count != 7) return -1;

    // The first token should be of type object
    if (count < 1 || t[0].type != JSMN_OBJECT) return -1;

    // Iterate through all the tokens from the container_spec.json file
    for (i = 1; i < 7; i++)
    {
        if (jsoneq(JSON_STRING, &t[i], "init") == 0) {
            // place key into a string
            char* myString = JSON_STRING + t[i+1].start;
            myString[t[i+1].end - t[i+1].start] = '\0';

            specs[0] = myString;
            i++;
        } else if (jsoneq(JSON_STRING, &t[i], "fs") == 0) {
            // place key into a string
            char* myString = JSON_STRING + t[i+1].start;
            myString[t[i+1].end - t[i+1].start] = '\0';

            specs[1] = myString;
            i++;
        } else if (jsoneq(JSON_STRING, &t[i], "nproc") == 0) {
            // place key into a string
            char* myString = JSON_STRING + t[i+1].start;
            myString[t[i+1].end - t[i+1].start] = '\0';

            specs[2] = myString;           
            i++;
        } else {
            // Unexpected token in the .json file
            return -1;
        }
    }
    // success
    return 0;
}