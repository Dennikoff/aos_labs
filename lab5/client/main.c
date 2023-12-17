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
  long type;
  int id;
  char data[20];
  int count;
};

void sighandler(int signum)
{
  if (msgctl(id, IPC_RMID, 0) == -1) {
    perror("Error 1 with msgctl!");
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

  signal(SIGINT, handler);

  printf("key = %d\n", key);
  int msgId;
  if ((msgId = msgget(key, (S_IRUSR | S_IWUSR | IPC_CREAT))) < 0) {
    onError(msgId, "msgget");
  }

  while (1) {
    
  }

  return 0;
}