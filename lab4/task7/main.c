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
#include <limits.h>

int writeFunc(int file)
{
    char* temp = "3333\n";
    write(file, temp, strlen(temp) * sizeof(char));
}

int readFunc(int file)
{
    int readCount;
    char temp[10];
    readCount = read(file, temp, 10);
    if (readCount == 0) {
        return -1;
    }
    printf("Read from file: %s\n", temp);
}

int main(int argc, char **argv)
{
    const char *fName = "test.txt";

    int file, readCount;

    int childId = fork();

    if (childId == 0)
    {
        printf("Child\n");
        char temp[10];
        file = open(fName, O_RDONLY);
        sleep(1);
        if (file < 0)
        {
            perror("Error in open");
            exit(-1);
        }
        for (int i; i < 50; ++i)
        {
            int tempVal;
            if ((tempVal = readFunc(file)) == -1) {
                // break;
            }
        }
        close(file);
    }
    else
    {
        printf("Parent\n");
        file = open(fName, O_WRONLY | O_TRUNC);
        
        if (file < 0)
        {
            perror("Error in open");
            exit(-1);
        }
        for (int i; i < 50; ++i)
        {
            writeFunc(file);
            
        }
        close(file);
    }

    return 0;
}