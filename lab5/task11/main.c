#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

struct message {
  long mtype;
  char mtext[80];
};



int main(int argc, char** argv) {

  struct message Message;
  Message.mtype = 10;
  strcpy(Message.mtext, "im ready");
  int msgId = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR);
  printf("msgid = %d\n", msgId);
  char temp[10];
  int fileIn = open("testIn.txt", O_RDWR); //STDIN_FILENO;//
  int fileOut = open("testOut.txt", O_RDWR | O_TRUNC); //STDOUT_FILENO;//
  int childId = fork();

  
  
  if(childId == 0) {
    printf("CHILD \n");
    // sleep(1);
    while(1) {
      msgrcv(msgId, &Message, sizeof(struct message), 5, 0);
      int readCount = read(fileIn, temp, 10);
      if(readCount <= 1) {
        break;
      }
      write(fileOut, "Child:", sizeof("Child:"));
      write(fileOut, temp, readCount);
      write(fileOut, "\n", 1);
      Message.mtype = 10;
      msgsnd(msgId, &Message, sizeof(struct message), 0);
    }
    

  } else {
    printf("PARENT \n");
    while(1) {
      int readCount = read(fileIn, temp, 10);
      if(readCount <= 1) {
        break;
      }
      write(fileOut, "Parent:", sizeof("Parent:"));
      write(fileOut, temp, readCount);
      write(fileOut, "\n", 1);
      Message.mtype = 5;
      msgsnd(msgId, &Message, sizeof(struct message), 0);
      msgrcv(msgId, &Message, sizeof(struct message), 10, 0);
    } 
    
  }

  
  if(msgctl(msgId, IPC_RMID, NULL) < 0) {
    perror("msgctl error");
  }
  

  

  return 0;

  

  

}