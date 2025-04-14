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
  char data[500];
  if(fd == -1){  	
  	perror("fifo open in O_WRONLY failed");
  	}
  
  sprintf(data,"statement 1 \nstatement 2 \nstatement 3 \nstatement 4 \nstatement 5 \n");
  write(fd,data,strlen(data));	
  	
  close(fd);
  
  }
  
