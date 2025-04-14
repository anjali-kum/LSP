#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{

pid_t myPid;
pid_t myPPid;
pid_t child;

child=fork();
myPid = getpid();
myPPid = getppid();

if(child!=0){sleep(1);}

else{sleep(2);}


printf("\nhello from fork1 %d child of %d\n",myPid,myPPid);

}
