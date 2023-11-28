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

int main(int argc, char** argv) {
    int chanelDesk[2];
    char temp[20];
    pipe(chanelDesk);
    int childId = fork();
    if(childId == 0) {
        printf("Child\n");
        close(chanelDesk[0]);
        int readCount;
        char fileIn[2];
        char fileOut[2];
        sprintf(fileIn, "%d", 0);
        sprintf(fileOut, "%d", chanelDesk[1]);
        execl("exec.out", "exec.out", fileIn, fileOut, NULL);

    } else {
        printf("Parent\n");
        sleep(1);
        close(chanelDesk[1]);
        int readCount;
        while((readCount = read(chanelDesk[0], temp, 20)) > 0) {
            printf("some info from child: %s\n", temp);
            // write(1, temp, readCount);
        }
        close(chanelDesk[0]);

    }
    return 0;
}