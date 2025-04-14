#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/ipc.h>

int main(){
int i=5;

printf(" %d ftok(\"./key.txt\",%d)= %d\n",__LINE__,i,ftok("./key.txt",i));

printf(" %d ftok(\"./key2.txt\",%d)= %d\n",__LINE__,i,ftok("./key2.txt",i));


return 0;
}


