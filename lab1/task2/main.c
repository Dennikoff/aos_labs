#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("Invalid number of parametres\n");
        return -1;
    }
    int file;
    char* filename = argv[1];
    int permissions =  strtol(argv[2], NULL, 8);
    if((file = open(filename, O_RDWR | O_CREAT, permissions)) == -1) {
        perror("Error in opening file");
    } else {
        const char someString1[] = "string 1";
        const char someString2[] = "string 2";
        const char someString3[] = "string 3";
        write(file, someString1, sizeof(char) * (strlen(someString1)));
        write(file, someString2, sizeof(char) * (strlen(someString2)));
        write(file, someString3, sizeof(char) * (strlen(someString3)));
    }
    close(file);
    int temp_res, temp_lseek;
    if((file = open(filename, O_RDONLY)) == -1) {
        perror("Error in opening file");
    } else {
        const int fileSize = lseek(file, 0, SEEK_END);
        char buf[64];
        temp_lseek = lseek(file, 0, SEEK_SET);
        if(temp_lseek == -1) {
            perror("Lseek Error");
        }
        temp_res = read(file, buf, fileSize);
        if(temp_res == -1) {
            perror("Read Error");
        }
        printf("File content:\n%s\n------------\n", buf);
    }
    close(file);
    if((file = open(filename, O_RDWR)) == -1) {
        perror("Error in opening file");
    } else {
        printf("Open successfully\n");
    }
	return 0;
}