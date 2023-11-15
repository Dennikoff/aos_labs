#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct sigaction newAct1, newAct2;


int count = 0;

void sigPrint(int sigNum) {
    printf("Get signal %d\n", sigNum);
}

void sigHandler(int sigNum) {
    printf("Get signal %d\n", sigNum);
    if(sigNum == SIGUSR1) {
        sigset_t procMask;
        sigemptyset(&procMask);
        sigaddset(&procMask, SIGUSR2);
        sigprocmask(SIG_BLOCK, &procMask, NULL);
        printf("start sleep\n");
        sleep(5);
        printf("end sleep\n");
        sigprocmask(SIG_UNBLOCK, &procMask, NULL);
    }
    // printf("Count: %d\n", ++count);
    // sleep(2);
    // printf("End signal: %d\n", sigNum);
}



int main(int argc, char** argv) {
    
    printf("Pid: %d\n", getpid());

    const int childId = fork();
    if(childId == 0) {
        printf("Im child pid: %d \n", getpid());
        
        newAct1.sa_handler = sigHandler;

        newAct2.sa_handler = sigPrint;

        if(sigaction(SIGUSR1, &newAct1, NULL) == -1) {
            perror("Sigaction error");
            exit(0);
        }

        if(sigaction(SIGUSR2, &newAct2, NULL) == -1) {
            perror("Sigaction error");
            exit(0);
        }
        int i;

        for(i = 0; i < 100; ++i) {
            printf("i = %d\n", i);
            sleep(1);
        }
        // if(sigaction(SIGUSR2, newAct1, NULL) == -1) {
        //     perror("Sigaction error");
        //     exit(0);
        // }
        exit(5);
    } else {
        printf("Im parent pid: %d \n", getpid());
        int status;
        sleep(1);
        printf("Send SIGUSR1\n");
        kill(childId, SIGUSR1);
        sleep(1);
        printf("Send SIGUSR2\n");
        kill(childId, SIGUSR2);
        kill(childId, SIGUSR2);
        kill(childId, SIGUSR2);
        waitpid(childId, &status, 0);

        if(WIFEXITED(status)){
            int exitStatus = WEXITSTATUS(status);
            printf("Exit status %d\n", exitStatus);
        } else {
            printf("Child exited incorrectly with status %d\n", status);
        }
    }
    return 0;
}