#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv, char** envp) {
    pid_t parentId = getpid();
    pid_t childId = fork();
    if(getpid() == parentId) {
        printf("\nI am parent\n");
        printf("Pid: %d\n", getpid());
        printf("Parent Pid: %d\n", getppid());
        printf("Gid: %d\n", getgid());
        pause();
        printf("\n-------------\n");
    } else {
        printf("\nI am child\n");
        printf("Pid: %d\n", getpid());
        printf("Parent Pid: %d\n", getppid());
        printf("Gid: %d\n", getgid());
        pause();
    }
    
}
