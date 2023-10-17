#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    int file;
    if(argc != 2) {
        printf("Invalid number of parametres\n");
        return -1;
    }
    char* filename = argv[1];
    if((file = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600)) == -1) {
        perror("Error in opening file");
    } else {
        int temp_res;
        int temp_lseek;
        char someString1[] = "string 1: My name is Denis";
        
        temp_res = write(file, someString1, sizeof(char) * sizeof(someString1));
        if(temp_res == -1) {
            perror("Write Error");
        }
        
        temp_lseek = lseek(file, 100, SEEK_END);
        if(temp_lseek == -1) {
            perror("Lseek Error");
        }
        
        const char tempString2[] = "string 2:";
        printf("Sizeof string 2: %d\n", sizeof(char) * sizeof(tempString2));

        temp_res = write(file, tempString2, sizeof(char) * sizeof(tempString2));
        if(temp_res == -1) {
            perror("Write Error");
        }

        const int fileSize = lseek(file, 0, SEEK_END);
        printf("file Size: %d\n", fileSize);
        
        temp_lseek = lseek(file, 50, SEEK_SET);
        if(temp_lseek == -1) {
            perror("Lseek Error");
        }

        temp_res = write(file, tempString2, sizeof(char) * sizeof(tempString2));
        if(temp_res == -1) {
            perror("Write Error");
        }


    }
    close(file);
	return 0;
}