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
            fcntl(0, F_SETLKW, lock);

            printf("Child: %s\n", temp);

            lock.l_type = F_UNLCK;
            fcntl(0, F_SETLKW, lock);
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
            lock.l_type = F_WRLCK;
            fcntl(0, F_SETLKW, lock);

            printf("Parent: %s\n", temp);
            
            lock.l_type = F_UNLCK;
            fcntl(0, F_SETLKW, lock);
        }
    }

    return 0;
}