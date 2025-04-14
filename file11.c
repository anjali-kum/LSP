      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       
     
char data[100];       
       
int main (void){
int fd,fd_stdout,fd2,len=5;  

fd=open("abc2.txt",O_RDWR|O_CREAT|O_APPEND,0660);
/*
write(fd,"hello world\n",sizeof("hello world\n")-1);
write(fd,"hello world\n",sizeof("hello world\n")-1);
write(fd,"hello world\n",sizeof("hello world\n")-1);
write(fd,"hello world\n",sizeof("hello world\n")-1);
write(fd,"hello world\n",sizeof("hello world\n")-1);
write(fd,"hello world\n",sizeof("hello world\n")-1);
write(fd,"hello world\n",sizeof("hello world\n")-1);
*/


write(fd,"hello world\n",sizeof("hello world\n"));
write(fd,"hello world\n",sizeof("hello world\n"));
write(fd,"hello world\n",sizeof("hello world\n"));
write(fd,"hello world\n",sizeof("hello world\n"));
write(fd,"hello world\n",sizeof("hello world\n"));
write(fd,"hello world\n",sizeof("hello world\n"));
write(fd,"hello world\n",sizeof("hello world\n"));

printf("end of program\n");

 close(fd);

}

/*
fd_stdout=dup(1);

printf("fd of stdout is copied to index %d of fd table\n", fd_stdout);  
write(fd_stdout,"printing on terminal with fd_stdout\n",sizeof("printing on terminal with fd_stdout\n")-1);
  
  if((fd2=dup2(fd,1))==-1)perror("dup2");
  
write(fd_stdout,"dup2() completed\n",sizeof("dup2() completed\n")-1);
  
  
  printf("printf printing to file using FD %d copied to FD1\n", fd_stdout);
  printf("2 + 3 = %d\n",2+3);
  printf("hello world\n");
    
    
      
 if((fd2=dup2(fd_stdout,1))==-1)perror("dup2");
  
write(fd_stdout,"dup2() completed again\n",sizeof("dup2() completed again\n")-1);

printf("end of program\n");

 close(fd);

}



fd=dup(1);
printf("fd value is %d\n",fd);
//sleep(5);
//write(fd,"writing with fd\n",sizeof("writing with fd\n"));
       close(fd);
*/
