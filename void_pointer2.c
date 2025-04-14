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
printf("arg received is %c when converted to char\n",*((char *)arg));
printf("arg received is %f when converted to int\n",*((float *)arg));
printf("\n\n\n");

}

void * fun2(void *arg){

printf("arg received is %d when converted to int\n",*((int *)arg));
printf("arg received is %c when converted to char\n",*((char *)arg));
printf("arg received is %f when converted to int\n",*((float *)arg));
printf("\n\n\n");

}

void * fun3(void *arg){

printf("arg received is %d when converted to int\n",*((int *)arg));
printf("arg received is %c when converted to char\n",*((char *)arg));
printf("arg received is %f when converted to int\n",*((float *)arg));
printf("\n\n\n");

}


int main(){
int val1 = 3139;
char x ='B';
float pi = 3.14;

fun1(&val1);
fun2(&x);
fun3(&pi);

}



