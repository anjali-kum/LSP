#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>
#include<sys/msg.h>

#define my_mq 111

//user defined message structure or array
typedef struct {
long type;
char Uname[20];
char msg[50];
}My_Type;

int main(){

int msgid,ret;
struct msqid_ds buf;

My_Type my_msg;

/* get the  queue id for the existing queue*/
msgid=msgget(my_mq,0);

if(msgid>=0){
printf("Existing message Queue id = %d\n",msgid);

 msgctl(msgid, IPC_STAT, &buf);



	printf("message status  \n");
	printf("Time of last msgsnd buf.msg_stime : %ld\n",buf.msg_stime);
	printf("Time of last msgrcv buf.msg_rtime : %ld\n",buf.msg_rtime);
	printf("Time of creation or last buf.msg_ctime : %ld\n",buf.msg_ctime);
	printf("modification by msgctl()\n");
	
	printf("bytes in queue  buf.msg_cbytes : %ld\n",buf.msg_cbytes);
	printf("number of messages in queue buf.msg_qnum : %ld\n",buf.msg_qnum);
	printf("Maximum # of bytes in queue buf.msg_qbytes : %ld\n",buf.msg_qbytes);
	printf("PID of last msgsnd buf.msg_lspid %d\n",buf.msg_lspid);
	printf("PID of last msgrcv buf.msg_lrpid %d\n",buf.msg_lrpid);
	}
return 0;
}


