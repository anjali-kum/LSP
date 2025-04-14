#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

#define with_mutex 0 //false

int global =0;

typedef struct {
char name[10];
int id;
}msg;


pthread_mutex_t my_lock;

void * set_data(void *m1);
void * print_data(void *m1);



int main(){
pthread_t t1,t2;
msg m1;
#if with_mutex
pthread_mutex_init(&my_lock,NULL);
#endif


//thread_fun1(NULL);
pthread_create(&t1,NULL,set_data,&m1);

pthread_create(&t2,NULL,print_data,&m1);

printf("created both threads and waiting for both threads to complete execution\n");

pthread_join(t1,NULL);
printf("thread 1 completed execution\n");
pthread_join(t2,NULL);
printf("thread 2 completed execution\n");

}



void * set_data(void *m1){
#if with_mutex
pthread_mutex_lock(&my_lock);
#endif

printf("enter the name:\n");
scanf("%s",((msg *)m1)->name);

printf("enter the id:\n");
scanf("%d",&(((msg *)m1)->id));//sleep(1);

#if with_mutex
pthread_mutex_unlock(&my_lock);
#endif
}


void * print_data(void *m1){
sleep(1);

#if with_mutex
pthread_mutex_lock(&my_lock);
pthread_mutex_unlock(&my_lock);
#endif


printf("name: %s\n",((msg *)m1)->name);
printf("id:%d\n",((msg *)m1)->id);
}

