#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>

pid_t my_pid,my_ppid;
char msg[50];
int len;

void my_function1(int sig){
len = sprintf(msg,"we have received signal no %d\n", sig);
write(1,msg, len);
}

int main(){

signal(2,my_function1);
signal(45,my_function1);

my_pid=getpid();
my_ppid=getppid();

printf("my PID = %d\n",my_pid);
printf("my PPID = %d\n",my_ppid);

while(1);
}

