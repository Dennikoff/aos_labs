#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Invalid number of parameters\n");
        return -1;
    }
    
    system(argv[1]);
    return 0;
}