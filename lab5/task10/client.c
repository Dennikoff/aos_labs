#include <unistd.h>
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
  char *prognameServer = "server.out";
  struct message Message;
  key_t keyServer = ftok(prognameServer, 0);
  if (keyServer < 0) {
    perror("ftok error");
    exit(-1);
  }

  signal(SIGINT, sighandler);

  printf("keyServer = %d\n", keyServer);
  
	int msgServer;
  if ((msgServer = msgget(keyServer, (S_IRUSR | S_IWUSR | IPC_CREAT))) < 0) {
    perror("msgget server error");
  }
  
  printf("msgServer = %d\n", msgServer);

  int type = atoi(argv[1]);
	Message.mtype = type;
	strcpy(Message.mtext, "some data");
	Message.midTo = msgServer;
  Message.midFrom = msgServer;
  while (1) {
		if (msgsnd(msgServer, &Message, sizeof(struct message), 0) < 0) {
        perror("msgrcv error");
        if (msgctl(msgId, IPC_RMID, 0) == -1) {
            perror("msgctl close error");
        }
        return -1;
    }
		if (msgrcv(msgServer, &Message, sizeof(struct message), type + 1, 0) < 0) { 
        perror("msgrcv error");
        if (msgctl(msgId, IPC_RMID, 0) == -1) {
            perror("msgctl close error");
        }
        return -1;
    }
    
		printf("Message recieve from server:\ntype: %ld\nid From: %d\nid To: %d\ndata: %s\n", Message.mtype, Message.midFrom, Message.midTo, Message.mtext);

    Message.mtype = Message.mtype - 1;
    Message.midTo = msgServer;
  	Message.midFrom = msgServer;
    strcpy(Message.mtext, "from client");

    sleep(2);
    

  }

  return 0;
}