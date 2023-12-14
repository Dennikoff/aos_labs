#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <limits.h>

int main(int argc, char **argv)
{
    struct flock rd_lock, wr_lock, unlock;
    
    rd_lock.l_type = F_RDLCK;
    rd_lock.l_whence = SEEK_SET;
    rd_lock.l_start = 0;
    rd_lock.l_len = 0;

    wr_lock.l_type = F_WRLCK;
    wr_lock.l_whence = SEEK_SET;
    wr_lock.l_start = 0;
    wr_lock.l_len = 0;

    unlock.l_type = F_UNLCK;
    unlock.l_whence = SEEK_SET;
    unlock.l_start = 0;
    unlock.l_len = 0;

    char temp[10];
    int readCount;

    int inFile = open("testIn.txt", O_RDWR); //STDIN_FILENO;//
    int outFile = open("testOut.txt", O_RDWR | O_TRUNC); //STDOUT_FILENO;//


    int childId = fork();

    if (childId == 0)
    {
        printf("Child\n");
        
        while(1) {
            if(fcntl(inFile, F_SETLKW, &wr_lock) < 0){
                perror("Child FCNTL rd_lock error");
            }
            readCount = read(inFile, temp, 10);
            
            if(fcntl(inFile, F_SETLK, &unlock) < 0){
                perror("Child FCNTL rd_unlock error");
            }
            if(readCount <= 1) {
                return 0;
            }

            if(fcntl(outFile, F_SETLKW, &wr_lock) < 0){
                perror("Child FCNTL wr_lock error");
            }

            write(outFile, "Child:", sizeof("Child:"));
            write(outFile, temp, readCount);
            write(outFile, "\n", 1);

            if(fcntl(outFile, F_SETLK, &unlock) < 0){
                perror("Child FCNTL wr_unlock error");
            }

            // sleep(1); //with STDOUT and STDIN
        }
        

    }
    else
    {
        printf("Parent\n");
        while(1) {
            
            if(fcntl(inFile, F_SETLKW, &wr_lock) < 0){
                perror("Parent FCNTL rd_lock error");
            }
            readCount = read(inFile, temp, 10);
            
            if(fcntl(inFile, F_SETLK, &unlock) < 0){
                perror("Parent FCNTL rd_unlock error");
            }
            if(readCount <= 1) {
                return 0;
            }

            if(fcntl(outFile, F_SETLKW, &wr_lock) < 0){
                perror("Parent FCNTL wr_lock error");
            }

            write(outFile, "Parent:", sizeof("Parent:"));
            write(outFile, temp, readCount);
            write(outFile, "\n", 1);

            if(fcntl(outFile, F_SETLK, &unlock) < 0){
                perror("Parent FCNTL wr_unlock error");
            }

            // sleep(1); //with STDOUT and STDIN
        }
    }

    return 0;
}