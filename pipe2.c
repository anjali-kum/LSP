      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       #include <stdlib.h>
       
  pid_t pid, cpid;
  int fd[2];
  int len;
  char data1[100];
  
 int init(void);
 int myread(void);
 int mywrite(void);
 int myclose(void);
 int child(void);
 int parent(void);
 
  
  int main(){
  
  pid = getpid();
  printf("parent process is %d \n",pid);
  
  init();
  
  cpid = fork();
  
  switch(cpid){
  case -1: perror("fork");
  		exit(0);
  case 0: child(); break;
  
  default : parent();
  
  };
  
  myclose();
  exit(0);
  
  }
  
 int init(void){
 
 if(pipe(fd)==-1){
  perror("pipe:");
 }
 
 }
 
 
 int myread(void){
 	
	//write(1,"enter the data",sizeof("enter the data")-1);
	len = read(fd[0],data1,99);
	data1[len] = '\0';
	
	if(cpid == 0) write(1,"Child ::>> ",strlen("Child ::>> "));
	else write(1,"Parent ::>> ",strlen("Parent ::>> "));
	write(1,"data from pipe:\n",strlen("data from pipe:\n"));
	write(1,data1,strlen(data1));
 
 }
 
 int mywrite(void){
	write(1,"enter the string \n", sizeof("enter the string \n")-1);
	len = read(0,data1,99);
	if(len == -1){
	perror("my write -read : ");
	exit(0);
	}
	data1[len] = '\0';
	write(fd[1],data1,strlen(data1));
	//write(1,data1,strlen(data1));
	
 }
  
int myclose(void){
close(fd[0]);
close(fd[1]);

write(1,"pipes have been closed \n", sizeof("pipes have been closed \n")-1);
} 

int child(void){

close(fd[1]);
  while(1){
  myread();
  
  write(1,"above received from my Parent\n", sizeof("above received from my Parent\n")-1);
   }
close(fd[0]);
}

int parent(void){
close(fd[0]);

while(1){

  write(1,"parent : \n", sizeof("parent : \n")-1);
  mywrite(); 
  sleep(1);
  } 
  
close(fd[1]);
}
