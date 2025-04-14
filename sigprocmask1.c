
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>


int main(){
pid_t pid = getpid();
int sig_no;
sigset_t my_sig,old_sig;

printf("PID = %d\n",pid);

//clear mask variable
sigemptyset(&my_sig);

while(1){


printf("enter the signal to be blocked\n");
scanf("%d",&sig_no);


// set desired signals to block;
sigaddset(&my_sig,sig_no);

//assign sigaction variable to sigaction function
sigprocmask(SIG_SETMASK,&my_sig,&old_sig);
printf("blocked signal no %d\n type 123 to exit or anything elese to continue",sig_no);

scanf("%d",&sig_no);
if(sig_no==123)exit(0);

//sigprocmask(SIG_SETMASK,&old_sig,NULL);
}

}

