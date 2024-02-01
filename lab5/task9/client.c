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
  char *progname = argv[0];
  struct message Message;
  key_t keyServer = ftok(prognameServer, 0);
  if (keyServer < 0) {
    perror("ftok error");
    exit(-1);
  }

  key_t key = ftok(progname, 0);
  if (keyServer < 0) {
    perror("ftok error");
    exit(-1);
  }

  signal(SIGINT, sighandler);

  printf("keyServer = %d\n", keyServer);
  printf("key = %d\n", key);
	int msgServer;
  if ((msgServer = msgget(keyServer, (S_IRUSR | S_IWUSR | IPC_CREAT))) < 0) {
    perror("msgget server error");
  }

	if ((msgId = msgget(key, S_IWUSR | S_IRUSR | IPC_CREAT)) == -1) {
		perror("msgset client error");
	}
  int type = atoi(argv[1]);
	Message.mtype = type;
	strcpy(Message.mtext, "some data");
	Message.midTo = msgServer;
  Message.midFrom = msgId;
  while (1) {
		if (msgsnd(msgServer, &Message, sizeof(struct message), 0) < 0) {
        perror("msgrcv error");
        if (msgctl(msgId, IPC_RMID, 0) == -1) {
            perror("msgctl close error");
        }
        return -1;
    }
    
		if (msgrcv(msgId, &Message, sizeof(struct message), type, 0) < 0) { 
        perror("msgrcv error");
        if (msgctl(msgId, IPC_RMID, 0) == -1) {
            perror("msgctl close error");
        }
        return -1;
    }
    
		printf("Message recieve from server:\ntype: %ld\nid From: %d\nid To: %d\ndata: %s\n", Message.mtype, Message.midFrom, Message.midTo, Message.mtext);

    Message.midTo = msgServer;
  	Message.midFrom = msgId;
    

    sleep(2);
    

  }

  return 0;
}