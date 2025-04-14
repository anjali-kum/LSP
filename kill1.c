#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>

int main(){

int pid,sig;
pid_t mypid;

mypid =getpid();
printf("my pid is %d \n",mypid);

while(1){
printf("enter the id of the process : ");
scanf("%d",&pid);

printf("enter the signal number between 1 to 64 : ");
scanf("%d",&sig);

kill(pid,sig);

printf("Signal %d sent to Process %d \n",sig,pid);
}
}
