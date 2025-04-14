#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>

void my_function1(int sig){

printf("we have received signal no %d\n", sig);

}

void main(){
pid_t my_pid,my_ppid;
my_pid=getpid();
my_ppid=getppid();

signal(2,my_function1);

printf("my PID = %d\n",my_pid);
printf("my PPID = %d\n",my_ppid);

signal(3,my_function1);
while(1);

}

