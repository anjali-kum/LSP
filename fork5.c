#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{

pid_t myPid,c_pid;
pid_t myPPid;
pid_t child;
int child_status;
child = fork();
char e_status;
myPid = getpid();
myPPid = getppid();

switch(child)

{
case -1:
	printf("\nno child created\n ");
	break;

case 0:
	//child process

		printf("\nline %d :I am child %d my fork return value is %d\n",__LINE__,myPid,child);
	printf("please enter the exit status you want:\n");
	scanf("%d",&e_status);

	exit(e_status);
	break;

default:
	//parent

	printf("\nline %d :hello from %d I am the parent of child %d\n",__LINE__,myPid,child);

	c_pid=wait(&child_status);

	printf("line %d :received termination information of PID : %d\n",__LINE__,c_pid);

	printf("line %d :my child has returned exit status %d\t %X \t%d\n",__LINE__,child_status,child_status,WEXITSTATUS(child_status));
	//sleep(2);
}


return 0;
}
