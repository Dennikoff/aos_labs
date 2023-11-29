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
            printf("Child: %s\n", temp);
            // write(1, "Child:", sizeof("Child:"));
            // write(1, temp, readCount);
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
            printf("Parent: %s\n", temp);
            // write(1, "Parent:", sizeof("Parent:"));
            // write(1, temp, readCount);
            
        }
    }

    return 0;
}