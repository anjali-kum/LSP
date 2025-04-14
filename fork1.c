#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{

pid_t myPid;
pid_t myPPid;

fork();
myPid = getpid();
myPPid = getppid();
printf("\nhello from fork1 %d child of %d\n",myPid,myPPid);

}
