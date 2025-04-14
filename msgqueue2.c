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

My_Type my_msg;

/* get the  queue id for the existing queue*/
msgid=msgget(my_mq,0);

if(msgid>=0){
	printf("Existing message Queue id = %d\n",msgid);
	my_msg.type = 1L;
	strcpy(my_msg.Uname,"Viven");
	strcpy(my_msg.msg,"Good morning\n");

	ret = msgsnd(msgid, (struct msgbuf *)&my_msg, sizeof(My_Type),0 );

	if(ret !=-1){
	printf("message sent successfully\n");
	}
}

return 0;
}


