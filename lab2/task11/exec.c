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
    
    pid_t childId = fork();
    
    if (childId == 0) {
        printf("I'm child\n");

        int error = execv(argv[1], &argv[1]);
        if(error == -1) {
            perror("Error in execv");
        }
    }
    else {
        printf("I'm parent\n");
    }
    return 0;
}