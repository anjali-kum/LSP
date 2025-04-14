#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

pid_t my_pid, my_ppid,c_pid;
int e_status;

int parent(void);
int child(void);

int main()
{


printf("\nrunning program from file %s \n ",__FILE__);
	
	c_pid=wait(&e_status);	


c_pid = fork();

my_pid = getpid();
my_ppid = getppid();

switch(c_pid){
case -1://failed
	printf("\nno child created\n ");
	exit(0);
	break;
case 0:	//child process
	child(); break;

default://parent
	parent(); 
}

return 0;
}


int parent(void){

	printf("\nParent Processs line %d::> c_pid =%d, my_pid = %d, my_ppid =%d \n ",__LINE__,c_pid,my_pid, my_ppid);
	
	c_pid=wait(&e_status);	

if(WIFSIGNALED(e_status)){
	printf("\nParent Processs line %d::> c_pid =%d was terminated by signal no %d\n ",__LINE__,c_pid,WTERMSIG(e_status));
}
else{
	printf("\nParent Processs line %d::> c_pid =%d has exited with status %d\n ",__LINE__,c_pid,WEXITSTATUS(e_status));
}
}

int child(void){

	printf("\nChild Processs line %d::> c_pid =%d, my_pid = %d, my_ppid =%d \n ",__LINE__,c_pid,my_pid, my_ppid);
	printf("enter the exit status value\n");
	scanf("%d",&e_status);
	exit(e_status);
}

