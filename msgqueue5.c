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

int msgid;

msgid=msgget(my_mq,0666|IPC_CREAT|IPC_EXCL);


if(msgid==-1){
perror("msgget");
return 0;
}

else{
printf("Created a message Queue %d\n",msgid);
}
return 0;
}


