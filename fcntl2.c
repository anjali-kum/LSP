      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <sys/wait.h>     
       #include <string.h>
       #include <stdlib.h>
char data[100];       
       
int main (void){

int fd,fd_stdout,fd2,child;  

fd=open("abc3.txt",O_RDWR|O_CREAT|O_APPEND,0660);

dup2(fd,19);

      
child = fork();

if(child ==0){
execlp("./fcntl1", "./fcntl1", NULL);
printf("exec failed\n");
close(19);
}

else{
wait(NULL);
}

printf("end of program\n");


}
