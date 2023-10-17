#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int printReverse(int file) {
    char buf[1];
    int filesize = lseek(file, 0, SEEK_END);
    int lseekRes, readRes, writeRes;
    for(int i = filesize; i >= 0; --i) {
        lseekRes = lseek(file, i, SEEK_SET);
        if(lseekRes == -1) {
            perror("Error in lseek");
        }
        readRes = read(file, buf, sizeof(char) * sizeof(buf));
        if(readRes == -1) {
            perror("Error in read");
        }
        writeRes = write(STDOUT_FILENO, buf, sizeof(char) * sizeof(buf));
        if(writeRes == -1) {
            perror("Error in write");
        }
    }
    writeRes = write(STDOUT_FILENO, "\n", sizeof("\n"));
    if(writeRes == -1) {
        perror("Error in write");
    }
    return 0;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Invalid number of parametres\n");
        return -1;
    }
    char* filename = argv[1];
    int file;
    if((file = open(filename, O_RDONLY)) == -1) {
        perror("Error in open file");
    } else {
        printReverse(file);
    }

}