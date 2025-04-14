#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

int global =0;

void * thread_fun1(void *arg);




int main(){
pthread_t t1;
pthread_create(&t1,NULL,thread_fun1,NULL);

pthread_join(t1,NULL);

thread_fun1(NULL);
printf("\n Global variable at the end of execution%d\n",global);
}



void * thread_fun1(void *arg){
for(int i=0;i<5;i++){

printf("\n Global from thread loop %d",global);
global = i*10 + global;
sleep(1);
}
}

