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
int i=0;

printf(" %d ftok(\"./key.txt\",%d)= %d\n",__LINE__,i,ftok("./key.txt",i));
for(i=1;i<5000;i=i<<1)
printf(" %d ftok(\"./key.txt\",%d)= %d\n",__LINE__,i,ftok("./key.txt",i));
for(i=257;i<5000;i=i<<1)
printf(" %d ftok(\"./key.txt\",%d)= %d\n",__LINE__,i,ftok("./key.txt",i));

return 0;
}


