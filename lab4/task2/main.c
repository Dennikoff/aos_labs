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
        int readCount;
        // while((readCount = read(0, temp, 20)) > 1) {
        //     write(chanelDesk[1], temp, readCount);
        // }
        printf("child OUT\n");
        close(chanelDesk[0]);
        close(chanelDesk[1]);

    } else {
        printf("Parent\n");
        sleep(1);
        int readCount;
        while((readCount = read(chanelDesk[0], temp, 20)) > 0) {
            write(1, temp, readCount);
        }
        
        close(chanelDesk[0]);
        close(chanelDesk[1]);
    }
    return 0;
}