#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

struct message {
  long mtype;
  int midFrom;
  int midTo;
  char mtext[20];
};

  int msgId;

void sighandler(int signum) {
  if (msgctl(msgId, IPC_RMID, 0) == -1) {
    perror("msgctl close error");
  }
  printf("\nSTOP\n");
  exit(0);
}

int main(int argc, char **argv) {
  char *progname = argv[0];
  struct message Message;
  key_t key = ftok(progname, 0);
  if (key < 0) {
    perror("ftok error");
    exit(-1);
  }

  signal(SIGINT, sighandler);

  printf("key = %d\n", key);

  if ((msgId = msgget(key, (S_IRUSR | S_IWUSR | IPC_CREAT))) < 0) {
    perror("msgget error");
  }

  while (1) {
    if (msgrcv(msgId, &Message, sizeof(struct message), 10, 0) < 0) { // (msgrcv(id, Message, sizeof(struct message), 4, 0) for task 10
        perror("msgrcv error");
        if (msgctl(msgId, IPC_RMID, 0) == -1) {
            perror("msgctl close error");
        }
        return -1;
    }
    printf("Message recieve from client:\ntype: %ld\nid From: %d\nid To: %d\ndata: %s\n", Message.mtype, Message.midFrom, Message.midTo, Message.mtext);
    
    Message.midTo = Message.midFrom;
    Message.midFrom = msgId;

    if (msgsnd(Message.midTo, &Message, sizeof(struct message), 0) < 0) {
        perror("msgrcv error");
        if (msgctl(msgId, IPC_RMID, 0) == -1) {
            perror("msgctl close error");
        }
        return -1;
    }
    

  }

  return 0;
}