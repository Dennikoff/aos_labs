#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int copyFiles() {
    char buf[1];
    int readCount, writeCount;
    while(readCount = read(STDOUT_FILENO, buf, sizeof(char) * sizeof(buf))) {
        if(readCount == -1) {
            perror("Error in read");
            return -1;
        }
        writeCount = write(STDIN_FILENO, buf, sizeof(char) * sizeof(buf));
        if(writeCount == -1) {
            perror("Error in write");
            return -1;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    int saveOut, saveIn, fileOut, fileIn;
    if(argc != 3) {
        printf("Invalid number of parametres\n");
        return -1;
    } else {
        saveIn = dup(0);
        saveOut = dup(1);
        close(1);
        fileOut = open(argv[1], O_RDONLY);
        close(0);
        fileIn = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        if(fileOut == -1) {
            perror("Error file 'OUT'");
        }
        if(fileIn == -1) {
            perror("Error file 'IN'");
        }
    }
    int res = copyFiles();
    if(res != -1) {
        if(dup2(saveIn, STDIN_FILENO) == -1) {
            perror("Fail to return default 'in'");
        }
        if(dup2(saveOut, STDOUT_FILENO) == -1) {
            perror("Fail to return default 'out'");
        }
        const char successText[] = "Copied successfully\n";
        write(STDOUT_FILENO, successText, sizeof(char) * sizeof(successText));
        
    }

}