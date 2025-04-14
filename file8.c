      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       
     
char data[100];       
       
int main (void){
struct stat my_stat;
int fd,len;  

fd=open("abc.txt",O_RDWR|O_CREAT|O_APPEND,0660);

printf("hello from file8\n");
write(1,"welcome to program with write()\n",sizeof("welcome to program with write()\n")-1);

//write(fd,"\nnew test string tested again",sizeof("new test string tested again")-6);   
  
  len = read(fd,data,99);
  data[len]='\0';
  printf("\nlen = %d\n",len);
  printf("dat : %s",data);
  
  
  len = read(fd,data,99);
  data[len]='\0';
  printf("\nlen = %d\n",len);
  printf("dat : %s",data);
   
   
  len = read(fd,data,99);
  data[len]='\0';
  printf("\nlen = %d\n",len);
  printf("dat : %s",data);
       
       
       close(fd);
}


/*
fd=dup(1);
printf("fd value is %d\n",fd);
//sleep(5);
//write(fd,"writing with fd\n",sizeof("writing with fd\n"));
       close(fd);
*/
