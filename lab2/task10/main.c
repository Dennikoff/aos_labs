#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Invalid number of parameters\n");
        return -1;
    }
    
    pid_t childId = fork();
    
    if (childId == 0) {
        printf("I'm child\n");

        printf("Child %d args:\n", getpid());
        for (int i = 1; i < argc; ++i) {
            printf("Arg %d: %s\n", i, argv[i]);
        }

        char **env = environ;
        printf("Child env:\n");
        int i = 1;
        while (*env) {
            printf("%d: %s\n", i, *env);
            env++;
            ++i;
        }

        int error = execv(argv[1], &argv[1]);
        if(error == -1) {
            perror("Error in execv");
        }
    }
    else {
        int* status;
        wait(status);
        printf("I'm parent\n");

        printf("Parent %d args:\n", getpid());
        for (int i = 1; i < argc; ++i) {
            printf("Arg %d: %s\n", i, argv[i]);
        }

        char **env = environ;
        printf("Parent env:\n");
        int i = 1;
        while (*env) {
            printf("%d: %s\n", i, *env);
            env++;
            i++;
        }
    }
    return 0;
}