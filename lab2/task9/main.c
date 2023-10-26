#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int copy(int fileFrom, int fileTo) {
    char buf[1];
    int errorCode;
    while(errorCode = read(fileFrom, buf, sizeof(buf))) {
        if (errorCode == -1) {
            perror("error in reading");
        }
        write(fileTo, buf, sizeof(buf));
    }
    return 0;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Invalid number of parameters");
        return -1;
    }
    const char* filename = argv[1];
    
    pid_t childId = fork();
    
    int fileOut = open(filename, O_RDONLY);
    
    if (childId == 0) {
        printf("I'm child\n");
        int fileIn = open("fileOutChild.txt", O_RDWR | O_CREAT | O_TRUNC, 0700);
        copy(fileOut, fileIn);
    }
    else {
        printf("I'm parent\n");
        int fileIn = open("fileOutParent.txt", O_RDWR | O_CREAT | O_TRUNC, 0700);
        copy(fileOut, fileIn);
    }
    return 0;
}