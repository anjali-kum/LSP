      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       
     
char data[1001];       
       
int main (void){
struct stat my_stat;
int fd,len=5;  

fd=open("abc.txt",O_RDWR|O_CREAT|O_APPEND,0660);


write(fd,"\n\nthis is fault test",25);

       close(fd);
  
fd=open("abc.txt",O_RDWR|O_CREAT|O_APPEND,0660);     
       
       
printf("hello from file9\n");
write(1,"welcome to program with write()\n",sizeof("welcome to program with write()\n")-1);


  while(( len = read(fd,data,1000))!=0){
   data[len]='\0';
  printf("\nlen = %d\n",len);
  write(1,data,sizeof(data));
  //printf("dat : %s",data);
  }
  
  
  
  printf("end of file\n");
       close(fd);
}



