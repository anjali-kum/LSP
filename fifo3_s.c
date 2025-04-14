      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       #include <stdlib.h>
  
  pid_t pid;
  char str_pid[10]="my_data";
  int len;
  int server_fd,client_fd;
  char data[200];
  
  int init (void);  
  int my_read(void);  
  int end_session(void);  
  int my_write(void);
  
  
  int main(){
  init();
  while(1){
	  my_read();
	  my_write();
  	}
    end_session();
  }
  
  
  
   
  int init (void){
  pid = getpid();
  
  
  sprintf(data,"Server pid =%d\n",pid);
  write(1,data,strlen(data));
  
  write(1,"init server....\n",sizeof("init server....\n")-1);
  mkfifo("server_fifo",0640);
  write(1,"server created....\n",sizeof("server created....\n")-1);
  server_fd = open("server_fifo",O_RDWR,0664);
  write(1,"server started\n",sizeof("server started\n")-1);
    
  }
  
  int my_read(void){
  len = read(server_fd,data,sizeof(data)-1);
  data[len]='\0';
  
  write(1,data,strlen(data));
     
  }
  
  int end_session(void){
  close(server_fd);
  unlink("server_fifo");
  
  }
  
 int my_write(void){
 
 client_fd=open(data,O_RDWR,0664);
 
  sprintf(data,">> client fifo created:\n sending : ");
  write(1,data,strlen(data));

  sprintf(data,"hello from server\n");
  write(client_fd,data,strlen(data));
   
   
  write(1,data,strlen(data));
  	
  	close(client_fd);
  }
