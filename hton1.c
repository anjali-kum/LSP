#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<arpa/inet.h>

//#define PORTs 0x1234
//#define PORTl 0x12 34 56 78

int main(){



short int ps = 0x1234;
long int pl = 0x12345678;


printf("ps = %d = %p \n",ps,ps);
printf("htons(ps) = %d = %p\n",htons(ps),htons(ps));


printf("pl = %ld = %p \n",pl,pl);
printf("htonl(pl) = %ld = %p\n",htonl(pl),htonl(pl));


return 0;
}



