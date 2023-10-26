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
        printf("Pid before: %d\n", getpid());
        printf("Parent Pid before: %d\n", getppid());
        printf("Gid before: %d\n", getgid());
        
        // if(setpgid(0, 400) == -1) {
        //     perror("setpgid error");
        // }
        if(setpgrp() == -1) {
            perror("Setpgrp error");
        }
        printf("Pid before after: %d\n", getpid());
        printf("Parent Pid after: %d\n", getppid());
        printf("Gid after: %d\n", getgid());
        pause();
    }
    
}