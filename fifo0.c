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
  int fd = open("myfifo", O_WRONLY);
  char data[50];
  if(fd == -1){  	
  	perror("fifo open in O_WRONLY failed");
  	}
  write(fd,"apple_are red",sizeof("apple_are red")-1);
  close(fd);
  
  printf("write to fifo complete\n");
 // sleep(1);
  fd = open("myfifo", O_RDONLY);
  if(fd == -1){  	
  	perror("fifo open in O_RDONLY failed");
  	}
  	
  len = read(fd,data,49);
  data[len]='\0';
  
  printf("%s",data);
  
  }
