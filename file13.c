      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       
     
char data[100], msg[100];       
int fd;
int len, old_size, offset;  
struct stat my_stat;

int init_server(void){

fd =open("my_file.txt",O_RDWR|O_CREAT|O_APPEND,0660);

fstat(fd,&my_stat);
printf("size of server file is %ld bytes",my_stat.st_size);


strcpy(msg,"::server started::\n");
write(fd,msg,strlen(msg));
printf("%s",msg);


fstat(fd,&my_stat);
printf("size of server file is %ld bytes\n",my_stat.st_size);
old_size=my_stat.st_size;
offset = lseek(fd,0,SEEK_END);
close(fd);

}

int poll(){

fd =open("my_file.txt",O_RDWR|O_CREAT|O_APPEND,0660);

fstat(fd,&my_stat);

if(my_stat.st_size==old_size){
sleep(1);
//printf("no data update\n");
return 1;
}
old_size = my_stat.st_size;
return 0;
}

int my_read(){

printf("\n\n File Data ::>");

lseek(fd,offset,SEEK_SET);
len = read(fd,data,sizeof(data)-1);
data[len]='\0';

printf("%s\n", data);


close(fd);
return 1;
}
       
int main (void){

init_server();

while(1){
while(poll()); // keep the program occupied till data is updated in file
my_read();
}

}
