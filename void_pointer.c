#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>



void * fun1(void *arg){

printf("arg received is %d when converted to int\n",*((int *)arg));

}

void * fun2(void *arg){

printf("arg received is %c when converted to char\n",*((char *)arg));

}

void * fun3(void *arg){

printf("arg received is %f when converted to int\n",*((float *)arg));

}


int main(){
int val1 = 3139;
char x ='A';
float pi = 3.14;

fun1(&val1);
fun2(&x);
fun3(&pi);

}



