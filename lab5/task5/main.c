#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

struct message {
  long mtype;
  char mtext[80];
};



int main(int argc, char** argv) {

  if(argc < 3) {
    printf("Not enough arguments \n");
    exit(-1);
  }

  int msgId = atoi(argv[1]);
  if(msgId == 0) {
    printf("Error in atoi\n");
    exit(-1);
  }
  printf("msgId = %d\n", msgId);
  if(strcmp(argv[2], "open") == 0) {
    if ((msgget(msgId, (S_IRUSR | S_IWUSR | IPC_CREAT))) < 0) { 
      perror("Error in open");
    } else {
      printf("MessageList with ID = %d open Successfully\n", msgId);
    }
  } else {
    if(msgctl(msgId, IPC_RMID, NULL) < 0) {
    perror("Error in closing");
    } else {
      printf("MessageList with ID = %d closed Successfully\n", msgId);
    }
  }
  

  

  return 0;

  

  

}