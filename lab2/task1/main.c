#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char** argv, char** envp) {
    int index = 0;

    printf("\nEnviroment envp\n\n");
    while(envp[index]) {
        printf("%s\n", envp[index]);
        index++;
    }

    index = 0;
    printf("\nEnviroment environ\n\n");
    while(environ[index]) {
        printf("%s\n", environ[index]);
        index++;
    }
    
    int setEnvValue = setenv("TEST_ENV", "TEST_VALUE---------------------------------------------------", 1);
    if(setEnvValue == -1) {
        perror("Environ");
    } 
    
    printf("\nEnviroment AFTER\n\n");
    index = 0;
    while(environ[index]) {
        printf("%s\n", environ[index]);
        index++;
    }

}