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
    int chanelDeskChildWrite[2];
    int chanelDeskChildRead[2];
    char temp[100];
    pipe(chanelDeskChildWrite);
    pipe(chanelDeskChildRead);
    int childId = fork();
    if(childId == 0) {
        printf("Child\n");
        int readCount;
        close(chanelDeskChildWrite[0]);
        close(chanelDeskChildRead[1]);
        while(1) {
            if((readCount = read(0, temp, 20)) > 1) {
                printf("Child read from input stream: %s\n", temp);
                write(chanelDeskChildWrite[1], temp, readCount);
                readCount = read(chanelDeskChildRead[0], temp, 100);
                printf("Child read from parent: %s\n", temp);
            } else {
                break;
            }
        }
        printf("child OUT\n");

        close(chanelDeskChildWrite[1]);
        close(chanelDeskChildRead[0]);

    } else {
        printf("Parent\n");
        int readCount;
        close(chanelDeskChildWrite[1]);
        close(chanelDeskChildRead[0]);
        while(1) {
            readCount = read(chanelDeskChildWrite[0], temp, 100);
            if(readCount == 0) {
                break;
            }
            printf("Parent read from child: %s\n", temp);
            write(chanelDeskChildRead[1], temp, readCount);             
        }
        printf("parent OUT\n");

        close(chanelDeskChildWrite[0]);
        close(chanelDeskChildRead[1]);
    }
    return 0;
}