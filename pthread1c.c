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
void * thread_fun2(void *arg);

int main(){
int loop = 20,ret;
pthread_t tm,t1,t2;
pthread_create(&t1,NULL,thread_fun1,&loop);
pthread_create(&t2,NULL,thread_fun2,&loop);
sleep(60);
printf("\n %d\n",global);

}



void * thread_fun1(void *arg){
int i,loop,loc;
printf("\n %d\n",*(int *)arg);
loop = *(int*)arg;
for(i=0;i<loop;i++){
loc = global;
loc = global;
global = global +loc;

printf("\n %d\n",global);
sleep(1);
}
}

void * thread_fun2(void *arg){
int i,loop,loc;
printf("\n %d\n",*(int *)arg);
loop = *(int*)arg;
for(i=0;i<loop;i++){
loc = global;
global = global +loc;

printf("\n %d\n",global);
sleep(1);
}
}
