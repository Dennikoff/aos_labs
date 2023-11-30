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
    struct flock lock;
    
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    char temp[10];
    int readCount;


    int childId = fork();

    if (childId == 0)
    {
        printf("Child\n");

        while(1) {
            
            readCount = read(0, temp, 10);
            if(readCount <= 1) {
                break;
            }
            lock.l_type = F_WRLCK;
            // if(fcntl(STDOUT_FILENO, F_SETLKW, lock) < 0){
            //     perror("Child FCNTL lock error");
            // }
            if(flock(STDOUT_FILENO, LOCK_EX) == 0){
                printf("Child blocked\n");
            } else {
                printf("Child blocked error\n");
            }
            

            write(STDOUT_FILENO, "Child:", sizeof("Child:"));
            write(STDOUT_FILENO, temp, readCount);
            write(STDOUT_FILENO, "\n", 1);
            // lock.l_type = F_UNLCK;
            // fcntl(STDOUT_FILENO, F_SETLKW, lock);
            if(flock(STDOUT_FILENO, LOCK_UN) == 0){
                printf("Child unblocked\n");
            } else {
                printf("Child unblocked error\n");
            }
        }
        

    }
    else
    {
        printf("Parent\n");
        while(1) {
            
            readCount = read(0, temp, 10);
            if(readCount <= 1) {
                break;
            }
            // lock.l_type = F_WRLCK;
            // if(fcntl(STDIN_FILENO, F_SETLKW, lock) < 0){
            //     perror("Parent FCNTL lock error");
            // }
            if(flock(STDOUT_FILENO, LOCK_EX) == 0){
                printf("Parent blocked\n");
            } else {
                printf("Parent blocked error\n");
            }
            write(STDOUT_FILENO, "Parent:", sizeof("Parent:"));
            write(STDOUT_FILENO, temp, readCount);
            write(STDOUT_FILENO, "\n", 1);

            // lock.l_type = F_UNLCK;
            // fcntl(STDOUT_FILENO, F_SETLKW, lock);
            if(flock(STDOUT_FILENO, LOCK_UN) == 0){
                printf("Parent unblocked\n");
            } else {
                printf("Parent unblocked error\n");
            }
        }
    }

    return 0;
}