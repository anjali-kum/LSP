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
pthread_mutex_t my_mutex_lock;

void * thread_fun1(void *arg);
void * thread_fun2(void *arg);


int main(){
pthread_t t1,t2;

pthread_mutex_init(&my_mutex_lock,NULL);

pthread_create(&t1,NULL,thread_fun1,NULL);
pthread_create(&t2,NULL,thread_fun2,NULL);

printf("\n thread 1 id =%ld\n",t1);
printf("\n thread 2 id =%ld\n",t2);

pthread_join(t1,NULL);
pthread_join(t2,NULL);
pthread_mutex_destroy(&my_mutex_lock);
printf("\n Global variable at the end of execution%d\n",global);
}


void * thread_fun1(void *arg){
pthread_t thread_no=pthread_self();


pthread_mutex_lock(&my_mutex_lock);

printf("\n %ld crital code 1\n",thread_no);
for(int i=0;i<5;i++){
printf("\n Global from thread %ld loop %d\n",thread_no,global);
global = (global + i*10);
sleep(1);
}
pthread_mutex_unlock(&my_mutex_lock);

sleep(1);

pthread_mutex_lock(&my_mutex_lock);
printf("\n %ld crital code 2\n",thread_no);
for(int i=0;i<5;i++){
printf("\n Global from thread %ld loop %d\n",thread_no,global);
global = (global + i*10);
sleep(1);
}
pthread_mutex_unlock(&my_mutex_lock);
}



void * thread_fun2(void *arg){
pthread_t thread_no=pthread_self();

pthread_mutex_lock(&my_mutex_lock);

printf("\n %ld crital code 1\n",thread_no);
for(int i=0;i<5;i++){
printf("\n Global from thread %ld loop %d\n",thread_no,global);
global = (global + i*10);
sleep(1);
}
pthread_mutex_unlock(&my_mutex_lock);

sleep(1);

pthread_mutex_lock(&my_mutex_lock);
printf("\n %ld crital code 2\n",thread_no);
for(int i=0;i<5;i++){
printf("\n Global from thread %ld loop %d\n",thread_no,global);
global = (global + i*10);
sleep(1);
}
pthread_mutex_unlock(&my_mutex_lock);
}



