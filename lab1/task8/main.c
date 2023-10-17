#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int copyFiles(int fileOut, int fileIn) {
    char buf[1];
    int readCount, writeCount;
    while(readCount = read(fileOut, buf, sizeof(char) * sizeof(buf))) {
        if(readCount == -1) {
            perror("Error in read");
            return -1;
        }
        writeCount = write(fileIn, buf, sizeof(char) * sizeof(buf));
        if(writeCount == -1) {
            perror("Error in write");
            return -1;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    int fileIn, fileOut;
    if(argc != 3) {
        fileIn = STDIN_FILENO;
        fileOut = STDOUT_FILENO;
    } else {
        fileOut = open(argv[1], O_RDONLY);
        fileIn = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        if(fileOut == -1) {
            perror("Error file 'OUT'");
        }
        if(fileIn == -1) {
            perror("Error file 'IN'");
        }
    }
    int res = copyFiles(fileOut, fileIn);
    if(res != -1) {
       printf("Copy success\n");
    }

}