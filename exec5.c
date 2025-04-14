#include<stdio.h>
#include<unistd.h>


int main(int argc, char *args[]){
printf("welcome to %s\n",__FILE__);
//args[argc]=NULL;

printf("we have %d arguments\n",argc);
execlp(args[1],args[2],args[3],NULL);
printf("%s has called execl\n",__FILE__);
}
