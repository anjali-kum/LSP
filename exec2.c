#include<stdio.h>
#include<unistd.h>


int main(){

printf("welcome to %s\n",__FILE__);
execl("./fork6","fork6",NULL);


printf("%s has called execl\n",__FILE__);
}
