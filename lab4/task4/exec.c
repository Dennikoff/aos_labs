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
    if(argc < 3) {
        printf("Not enough params in exec func\n");
        exit(-1);
    }
    int fileIn = atoi(argv[1]);
    int fileOut = atoi(argv[2]);
    char temp[20];
    int readCount;
    while((readCount = read(fileIn, temp, 20)) > 1) {
        write(fileOut, temp, readCount);
    }
    printf("Exec out\n");
    close(fileOut);
    return 0;
}