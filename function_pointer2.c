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


int fun3(char *data){
printf("function 3 :> %s\n", data);
}


int fun4(char *data){
printf("function 4 :> %s\n", data);
}



int main(){
char data[50]= "hello from main";

int (*fn_ptr[4])(char *);

fn_ptr[0]=fun1;
fn_ptr[1]=fun2;
fn_ptr[2]=fun3;
fn_ptr[3]=fun4;

printf("main :> %s\n", data);

for(int i=0;i<4;i++){
(*fn_ptr[i])(data);

}


}

