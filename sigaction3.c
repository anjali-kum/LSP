#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>

void my_fun1(int sig){
int a;
printf("sign no %d received \n",sig);
printf("waiting in handler\n");
scanf("%d",&a);
//sleep(60);
}

int main(){
pid_t pid = getpid();

printf("PID = %d\n",pid);
struct sigaction act;

act.sa_handler = my_fun1;

//empty flags
act.sa_flags =0;

//clear mask
sigemptyset(&act.sa_mask);
// set desired signals to block during handler execution
sigaddset(&act.sa_mask,40);
sigaddset(&act.sa_mask,50);
//assign sigaction variable to sigaction function
sigaction(50,&act,NULL);
sigaction(40,&act,NULL);

while(1){
}
}

