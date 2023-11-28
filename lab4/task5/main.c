#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    int chanelDesk[2];
    char temp[20];
    pipe(chanelDesk);
    int childId = fork();
    if (childId == 0)
    {
        printf("Child\n");
        close(chanelDesk[0]);
        close(1);
        dup(chanelDesk[1]);
        close(chanelDesk[1]);
        execlp("who", "who", NULL);
    }
    else
    {
        printf("Parent\n");
        close(chanelDesk[1]);
        close(0);
        dup(chanelDesk[0]);
        close(chanelDesk[0]);
        execlp("wc", "wc", "-l", NULL);
    }
    return 0;
}