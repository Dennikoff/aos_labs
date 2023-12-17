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

void onError(int msgId, char* str) {
  
  char buf[20];
  sprintf(buf, "%s error", str);
  perror(buf);
  msgctl(msgId, IPC_RMID, NULL);
  exit(-1);
}

int main(int argc, char** argv) {
  char* progname = argv[0];
  key_t key = ftok(progname, 0);
  if(key < 0) {
    perror("ftok error");
    exit(-1);
  }

  printf("key = %d\n", key);

  int msgId;
  if ((msgId = msgget(key, (S_IRUSR | S_IWUSR | IPC_CREAT))) < 0) { 
      onError(msgId, "msgget");
  }

  printf("msgId = %d\n", msgId);

  struct message Message;
  
  
  if(strcmp(argv[1], "1") == 0) {
    strcpy(Message.mtext, "some data");
    for(int i = 1; i < 5; ++i) {
      Message.mtype = i;
      if(msgsnd(msgId, &Message, strlen(Message.mtext), 0) < 0) {
        onError(msgId, "msgsnd");
      }
  }
  } else {
    for(int i = 1; i < 5; ++i) {
      if(msgrcv(msgId, &Message, 3, i, MSG_NOERROR) < 0) {
        onError(msgId, "msgsnd");
      }
      printf("mtext message: %s\n", Message.mtext);
    }
    msgctl(msgId, IPC_RMID, NULL);
  }

  

  

}