#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>


int main(){
pid_t my_pid,my_ppid;
my_pid=getpid();
my_ppid=getppid();

printf("my PID = %d\n",my_pid);
printf("my PID = %d\n",my_ppid);

while(1);
}

