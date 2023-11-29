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
    if(argc < 2){
        printf("Not enough parameters\n"); 
        exit(-1);
    }
    bool mode = strcmp(argv[1], "1") == 0; // if 1 => twoways chanel  
    int chanelDesk[2];
    char temp[1];
    pipe(chanelDesk);
    int childId = fork();
    if(childId == 0) {
        printf("Child\n");
        int bytes = read(chanelDesk[0], temp, 1);
        if(bytes == -1){
            perror("Error in reading ");
            exit(-1);
        }
        printf("read from chanel in child: %s\n", temp);
        sleep(1);
        if(mode) {
            write(chanelDesk[1], "c", 1);
        }
        close(chanelDesk[0]);
        close(chanelDesk[1]);

    } else {
        printf("Parent\n");
        int bytes = write(chanelDesk[1], "p", 1);
        if(bytes == -1){
            perror("Error in reading ");
            exit(-1);
        }
        sleep(2);
        if(mode) {
            read(chanelDesk[0], temp, 1);
            printf("read from chanel in parent: %s\n", temp);
        }
        
        close(chanelDesk[0]);
        close(chanelDesk[1]);
    }
    return 0;
}