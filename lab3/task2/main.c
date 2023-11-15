#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


struct sigaction newAct, oldAct;

void sigHandler(int sigNum) {
    printf("Get signal %d\n", sigNum);
    sigaction(sigNum, &oldAct, NULL);
}


int main(int argc, char** argv) {
    printf("Pid: %d\n", getpid());
    newAct.sa_handler = sigHandler;
    newAct.sa_flags = 0;
    
    if(sigaction(SIGINT, &newAct, &oldAct) == -1) {
        perror("Sigaction Error");
        return -1;
    }
    pause();
}