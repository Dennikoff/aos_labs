#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv, char** environ) {
    int index = 0;
    printf("Enviroment\n");
    while(environ[index]) {
        printf("%s\n", environ[index]);
        index++;
    }
    
}