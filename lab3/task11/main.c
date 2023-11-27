#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct sigaction newAct, newAct2;


int count = 0;

void sigHandler(int sigNum) {
    printf("Get signal %d\n", sigNum);
}



int main(int argc, char** argv) {
    
    printf("Pid: %d\n", getpid());

    newAct.sa_handler = sigHandler;
    newAct.sa_flags = 0;
    sigemptyset(&newAct.sa_mask);
    sigaction(SIGUSR1, &newAct, NULL);

    newAct2.sa_handler = sigHandler;
    newAct2.sa_flags = 0;
    sigemptyset(&newAct2.sa_mask);
    sigaction(SIGUSR2, &newAct2, NULL);

    sigset_t syncMask;
    sigemptyset(&syncMask);
    sigaddset(&syncMask, SIGUSR1);
    sigaddset(&syncMask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &syncMask, NULL) == -1) {
        perror("Error with sigprocmask!");
    }
    const int childId = fork();
    if(childId == 0) {
        printf("Im child pid: %d \n", getpid());
        
        sigset_t tempMask;
        sigemptyset(&tempMask);

        printf("Start sleeping\n");
        sleep(5);


        printf("Sending SIGUSR1\n");

        kill(getppid(), SIGUSR1);
    } else {
        printf("Im parent pid: %d \n", getpid());
        

        sigset_t tempMask;
        sigemptyset(&tempMask);

        printf("Start suspending parent\n");
        sigsuspend(&tempMask);
        printf("Sync completed\n");
        
    }
    return 0;
}