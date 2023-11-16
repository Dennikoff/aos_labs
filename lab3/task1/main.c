#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void sigHandler(int sigNum) {
    printf("Get signal %d\n", sigNum);
    signal(sigNum, SIG_DFL);
}


int main(int argc, char** argv) {
    printf("Pid: %d\n", getpid());
    signal(SIGINT, sigHandler); // ctrl + c
    pause();
}