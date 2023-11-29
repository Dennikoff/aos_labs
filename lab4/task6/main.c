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

int main(int argc, char **argv)
{
    struct stat Stat; 
    // first run ./a.out and ./write.out on different terminals 
    //then type in write.out terminal
    int chanelDesk[2];
    char temp[20];
    const char* fName = "chanel";
    pipe(chanelDesk);
    if (stat(fName, &Stat) == -1) {
        perror("Error with stat!");
        exit(-1);
    }
    if(S_ISFIFO(Stat.st_mode)) printf("File is Fifo\n");

    int file, readCount;

    file = open(fName, O_RDONLY | O_NDELAY); //
    sleep(4); //
    while(read(file, temp, 20) > 0) {
        printf("Read from chanel %s", temp);
    }
    close(file);

    
    return 0;
}