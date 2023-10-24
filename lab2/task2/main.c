#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv, char** envp) {
    pid_t parentId = getpid();
    pid_t childId = fork();
    if(getpid() == parentId) {
        getchar();
        printf("I am parent\n");
    } else {
        getchar();
        printf("I am child\n");
    }
}