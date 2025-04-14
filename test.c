      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <fcntl.h>        
       #include <sys/stat.h>     
       #include <string.h>
       #include <stdlib.h>
       
int main (void){

printf("O_RDONLY =%d,  O_WRONLY=%d,  O_RDWR=%d\n",O_RDONLY ,O_WRONLY,O_RDWR);
printf("O_RDONLY =%p,  O_WRONLY=%p,  O_RDWR=%p\n",O_RDONLY ,O_WRONLY,O_RDWR);
printf("O_RDONLY | O_WRONLY| O_RDWR =%d\n",O_RDONLY |O_WRONLY|O_RDWR);
printf("O_RDONLY | O_WRONLY| O_RDWR =%p\n",O_RDONLY |O_WRONLY|O_RDWR);
}
