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

#define my_mq 112

//user defined message structure or array
typedef struct {
long type;
char Uname[20];
char msg[50];
}My_Type;

int main(){

int msgid;

msgid=msgget(my_mq,0666|IPC_CREAT);

if(msgid>=0){
printf("Created a message Queue %d\n",msgid);
}
return 0;
}


