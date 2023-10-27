#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv, char** envp) {
    pid_t parentId = getpid();
    pid_t childId = fork();
    if(getpid() == parentId) {
        printf("\nI am parent\n");
        printf("clildId %d\n", childId);
        printf("Pid: %d\n", getpid());
        printf("Parent Pid: %d\n", getppid());
        printf("Gid: %d\n", getgid());
        printf("\n-------------\n");
    } else {
        getchar();
        printf("\nI am child\n");
        printf("Pid: %d\n", getpid());
        printf("Parent Pid: %d\n", getppid());
        printf("Gid: %d\n", getgid());
    }
    
}

