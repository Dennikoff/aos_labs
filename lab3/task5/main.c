#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct sigaction newAct;

void sigHandler(int sigNum) {
    printf("Get signal %d\n", sigNum);
}


int main(int argc, char** argv) {
    printf("Pid: %d\n", getpid());
    newAct.sa_handler = sigHandler;
    newAct.sa_flags = SA_RESETHAND;
    const int childId = fork();
    if(childId == 0) {
        printf("Im child pid: %d \n", getpid());
        int i = 0, j = 0;
        for(int i = 0; i < 1000; ++i) {
            for (int j = 0; j < 1000; ++j) {
                printf("i = %d\n", i);
            }
        }
        
        // Задание 7
        // pause();

        exit(5);
    } else {
        printf("Im parent pid: %d \n", getpid());
        int status;
        sleep(1);
        kill(childId, SIGUSR1);
        // wait(&status);
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