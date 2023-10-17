#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Invalid number of parametres\n");
        return -1;
    }
    int maxFileLength = 0;
    int file, fileLength;
    for(int i = 1; i <= argc; ++i) {
        file = open(argv[i], O_RDONLY);
        fileLength = lseek(file, 0, SEEK_END);
        if(fileLength > maxFileLength) {
            maxFileLength = fileLength;
        }
    }
    char maxSize[5];
	sprintf(maxSize, "%d\n", maxFileLength);
    write(STDOUT_FILENO, maxSize, sizeof(char) * sizeof(maxSize));
    return 0;
}