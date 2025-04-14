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

void fun(int arg);

void fun1(void *arg);
void fun2(int *arg);


int main(){
int val =20;
void (* my_fptr)(int);

void (* my_fptr1)(void *);
void (* my_fptr2)(int *);


my_fptr = &fun;
my_fptr1 = &fun1;
my_fptr2 = &fun2;

(* my_fptr)(30);
(* my_fptr1)(&val);
(* my_fptr2)(&val);

}

void fun(int arg){
printf("arg received is %d \n",arg);

}

void fun1(void *arg){

printf("arg received is %d when converted to int\n",*((int *)arg));

}

void fun2(int *arg){

printf("arg received is %d \n",*arg);

}
