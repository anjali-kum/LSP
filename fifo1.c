      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       #include <stdlib.h>
       
  int main(){
  
  mkfifo("myfifo",0640);
  int len;
  int fd = open("myfifo", O_RDWR);
  char data[50];
  write(fd,"hello",sizeof("hello")-1);
  //sleep(2);
  len = read(fd,data,7);
  data[len]='\0';
  
  printf("%s",data);
  
  }
