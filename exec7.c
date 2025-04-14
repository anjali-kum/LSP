#include<stdio.h>
#include<unistd.h>


int main(int argc, char *args[]){
printf("welcome to %s\n",__FILE__);
args[argc] = '\0';
execvp(args[1],args+1);
printf("%s has called execl\n",__FILE__);
}
