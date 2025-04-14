      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       #include <stdlib.h>
char data[100];       
       
int main (void){

struct stat my_stat;
int fd =19;
int pid = getpid();

fstat(fd,&my_stat);
      
       printf(" Latest info related to fd = %d\n",fd);
       printf(" ID of device containing file = %ld\n",my_stat.st_dev);
       printf(" Inode number = %ld\n",my_stat.st_ino);
       printf(" User ID of owner = %d\n",my_stat.st_uid);
       printf(" Group ID of owner = %d\n",my_stat.st_gid);
       printf(" Total size, in bytes = %ld\n",my_stat.st_size);
       printf(" Block size for filesystem = %ld\n",my_stat.st_blksize);
       printf(" Number of 512B blocks allocated = %ld\n",my_stat.st_blocks);

for(int i =0; i<5;i++){
sprintf(data,"%d data : hello this is usinf fd = %d\n",pid,fd);
write(fd,data,strlen(data));
sleep(1);
}
perror("write to fd = 19");
close(fd);
perror("write to fd = 19");


printf("end of program\n");


}
