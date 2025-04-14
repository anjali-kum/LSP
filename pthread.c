#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

int main(){
int loop = 2000,ret;
pthread_t tm;
pid_t pid = getpid();

tm = pthread_self();
printf("Hi this is process PID =%d\n hi this is main thread thread id = %ld\n",pid,tm);
}



