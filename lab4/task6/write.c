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

int main(int argc, char **argv)
{
    char temp[20];
    const char* fName = "chanel";
    int file, readCount;

    file = open(fName, O_WRONLY | O_NDELAY);
    
    while((readCount = read(0, temp, 20)) > 1) {
       write(file, temp, readCount);
    }

    close(file);

    
    return 0;
}