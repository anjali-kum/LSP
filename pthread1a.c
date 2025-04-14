#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

int global =20;

void * thread_fun1(void *arg);


int main(){
int val1 = 2000,val2 = 3600;
pid_t pid = getpid();
pthread_t tmain,t1,t2;

tmain =  pthread_self();

printf("hello from %ld main thread\n",tmain);

thread_fun1(&val1);
thread_fun1(&val2);
printf("\n printing global from main thread %d\n",global);

}



void * thread_fun1(void *arg){
pthread_t thread_id = pthread_self();

printf("hello from %ld thread\n",thread_id);
printf("arg received is %d when converted to int\n",*((int *)arg));

}
