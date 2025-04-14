      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       #include <stdlib.h>
  
  pid_t pid;
  char str_pid[10]="hello";
  int len;
  int server_fd, client_fd;
  char data[200];
  
  int init (void);  
  int my_read(void);
  int my_write(void);     
  int end_session(void);
  
  
  int main(){
  init();
  my_write();
  my_read();
  end_session();
  }
  
  
  
  int init (void){
  pid = getpid();
  sprintf(str_pid,"%d",pid);
  
  server_fd = open("server_fifo",O_WRONLY,0664);
  if(server_fd==-1){
  printf("server not found\n");
  exit(0);
  }
  
  sprintf(data,"server found\n");
  write(1,data,strlen(data));
  
  mkfifo(str_pid,0640);
  
  client_fd = open(str_pid,O_RDWR,0664);
  
  sprintf(data,"client Fifo created and is open \n");
  write(1,data,strlen(data));
    
  }
  
  int my_read(void){
  
  
  sprintf(data,"Server msg received >> ");
  write(1,data,strlen(data));
  
  len = read(client_fd,data,sizeof(data)-1);
  data[len]='\0';
  
  write(1,data,strlen(data));
     
  }
  

  int my_write(void){
   write(server_fd,str_pid,strlen(str_pid));
   
  sprintf(data,"%s >> ", str_pid);
  write(1,data,strlen(data));
  
  
  }
  
    
  int end_session(void){
  close(server_fd);
  close(client_fd);
  unlink(str_pid);
  
  }
