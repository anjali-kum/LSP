      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       

       #include <fcntl.h>        
       #include <sys/stat.h>

int main (void){

struct stat my_stat;
int fd;

       
fd=open("mytext.txt",O_RDONLY);

       printf("\n\nfile was opened in FD no : %d\n\n",fd);
	
	fstat(fd,&my_stat);
      
       printf(" Latest info related to mytext.txt\n");
       printf(" ID of device containing file = %ld\n",my_stat.st_dev);
       printf(" Inode number = %ld\n",my_stat.st_ino);
       printf(" User ID of owner = %d\n",my_stat.st_uid);
       printf(" Group ID of owner = %d\n",my_stat.st_gid);
       printf(" Total size, in bytes = %ld\n",my_stat.st_size);
       printf(" Block size for filesystem = %ld\n",my_stat.st_blksize);
       printf(" Number of 512B blocks allocated = %ld\n",my_stat.st_blocks);
       
       close(fd);
}
