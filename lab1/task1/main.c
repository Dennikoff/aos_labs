#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int arhc, char** argv) {
	int file;
	if((file = open("test", O_RDONLY)) == -1) {
		char errnoString[20];
		int size = sprintf(errnoString, "errno: %d\n", errno);
		write(STDOUT_FILENO, errnoString, sizeof(char) * strlen(errnoString));
		printf("Sys errlist 1: %s\n", strerror(errno));
		// printf("Sys errlist 2: %s\n", sys_errlist[errno]);
		perror("Perror");
	}
	close(file);
	return 0;
}
