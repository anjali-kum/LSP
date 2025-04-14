#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>

int fun1(char *data){
printf("function 1 :> %s\n", data);
}


int fun2(char *data){
printf("function 2 :> %s\n", data);
}



int main(){
char data[50]= "hello from main";

int (*fn_ptr)(char *)=&fun2;

printf("main :> %s\n", data);
fun1(data);
(*fn_ptr)(data);

}

