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
    const char *fName = "test.txt";
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    int file, readCount;

    int childId = fork();

    if (childId == 0)
    {
        printf("Child\n");
        char temp[10];
        file = open(fName, O_RDONLY);
        for (int i = 0; i < 50; ++i)
        {
            lock.l_type = F_WRLCK;
            fcntl(file, F_SETLKW, lock);
            // if (flock(file, LOCK_EX) < 0){
            //     perror("flock error");
            // }
            readCount = read(file, temp, 10);
            // if (flock(file, LOCK_UN) < 0){
            //     perror("flock error");
            // }
            lock.l_type = F_UNLCK;
            fcntl(file, F_SETLKW, lock);
            printf("Read from file: %s\n", temp);
        }
        close(file);
    }
    else
    {
        char* temp = "12345\n";
        printf("Parent\n");
        printf("%d", file = open(fName, O_WRONLY | O_TRUNC));
        for (int i = 0; i < 50; ++i)
        {
            // lock.l_type = F_WRLCK;
            // fcntl(file, F_SETLKW, lock);
            write(file, temp, strlen(temp) * sizeof(char));
            // lock.l_type = F_UNLCK;
            // fcntl(file, F_SETLKW, lock);
        }
        close(file);
    }

    return 0;
}