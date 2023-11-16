#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


struct sigaction newAct;

void sigHandler(int sigNum) {
    printf("Get signal %d\n", sigNum);
}


int main(int argc, char** argv) {
    printf("Pid: %d\n", getpid());
    newAct.sa_handler = sigHandler;
    newAct.sa_flags = SA_RESETHAND;

    const int pid = fork();
    if(pid == 0) {
        printf("Im child pid: %d \n", getpid());
    } else {
        printf("Im parent pid: %d \n", getpid());

        if(sigaction(SIGCHLD, &newAct, NULL) == -1) {
            perror("Sigaction Error");
            return -1;
        }
        pause();
    }
    return 0;
}