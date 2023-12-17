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
  struct msqid_ds msgInfo;
  key_t key = ftok(progname, 0);
  if(key < 0) {
    perror("ftok error");
    exit(-1);
  }

  printf("key = %d\n", key);

  int msgId;
  if ((msgId = msgget(key, (S_IRUSR | S_IWUSR | IPC_CREAT))) < 0) { // S_IRUSR | S_IWUSR |
      onError(msgId, "msgget");
  }



  printf("msgId = %d\n", msgId);

  struct message Message;

  strcpy(Message.mtext, "some data");

  for(int i = 1; i < 5; ++i) {
      Message.mtype = i;
      if(msgsnd(msgId, &Message, strlen(Message.mtext), 0) < 0) {
        onError(msgId, "msgsnd");
      }
  }




  if (msgctl(msgId, IPC_STAT, &msgInfo) < 0) {
    onError(msgId, "msgctl stat");
  }
  
  printf("\nmsg_stime = %s", ctime(&msgInfo.msg_stime)); // send time
  printf("msg_rtime = %s", ctime(&msgInfo.msg_rtime)); // received time
  printf("msg_ctime = %s", ctime(&msgInfo.msg_ctime)); // control time
  printf("msg_qnum = %ld\n", msgInfo.msg_qnum); // mesage count
  printf("msg_qbytes = %ld\n", msgInfo.msg_qbytes); // max size of queue
  printf("msg_lspid = %d\n", msgInfo.msg_lspid); // last send pid
  printf("msg_lrpid = %d\n", msgInfo.msg_lrpid); // last received pid
  printf("msg_perm.uid = %d\n", msgInfo.msg_perm.uid); 
  printf("msg_perm.gid = %d\n", msgInfo.msg_perm.gid);
  printf("msg_perm.cuid = %d\n", msgInfo.msg_perm.cuid); // create uid
  printf("msg_perm.cgid = %d\n", msgInfo.msg_perm.cgid); // create gid
  printf("msg_perm.mode = %o\n", msgInfo.msg_perm.mode); // permisions
  printf("msg_perm.__key = %d\n", msgInfo.msg_perm.__key);

    msgctl(msgId, IPC_RMID, NULL);
}