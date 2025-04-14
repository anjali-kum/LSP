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

#define PORT 8080
#define MULTICAST_GROUP "239.0.0.1"

//user defined functions
int creat_sock(void);
//int set_sock(void);
int bind_sock(void);
int sub_mc_mode(void);
//int read_sock(void);
int write_sock(void);
int unsub_mc_mode(void);



int server_fd;
struct sockaddr_in address;
int msg_len;
int addrlen = sizeof(address);
char buffer[1024]={0};
struct ip_mreq mreq;

int main(){

creat_sock();
bind_sock();
sub_mc_mode();
while(1){
//read_sock();
write_sock();
}

unsub_mc_mode();
close(server_fd);
}



int creat_sock(void){

// creat a socket SOCK_DGRAM => UDP
if((server_fd = socket(AF_INET, SOCK_DGRAM, 0))<0){
perror("socket failed");
exit(EXIT_FAILURE);
}

}


int bind_sock(void){

memset(&address,'\0',sizeof(address));
address.sin_family = AF_INET;
address.sin_port = htons(PORT);
//in normal UDP
//address.sin_addr.s_addr = INADDR_ANY;
//in multicasting UDP
 inet_pton(AF_INET,MULTICAST_GROUP,&address.sin_addr);
 
 // Set the socket to allow multiple connections on the same port
 int opt =1;
 if(setsockopt(server_fd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))<0){
 perror("setsockopt");
exit(EXIT_FAILURE);
}

 
 
//Bind the socket to a port
if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
perror("bind failed");
exit(EXIT_FAILURE);
}

}


int sub_mc_mode(void){
// set the socket to multicast mode
mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
mreq.imr_interface.s_addr = htonl(INADDR_ANY);


 if(setsockopt(server_fd,IPPROTO_IP,IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))<0){
 perror("setsockopt");
exit(EXIT_FAILURE);
}
}
//multicast sender, read not required
/*
int read_sock(void)
{
msg_len = recvfrom(server_fd,(char *)buffer,1023,MSG_WAITALL, (struct sockaddr *)&address, &addrlen);
buffer[msg_len]='\0';
printf("client::> %s\n",buffer);

}
*/

int write_sock(void){

printf("\nEnter the message to send (or 'exit' to quit):");
fgets(buffer,sizeof(buffer),stdin);
buffer[strcspn(buffer,"\n")] = '\0';

if(strcmp(buffer,"exit")==0){
exit(0);
}

//send response to client
sendto(server_fd, (const char *)buffer, strlen(buffer),0,(const struct sockaddr *)&address, sizeof(address));
printf("\n");

}


int unsub_mc_mode(void){
//leaving the multicasting group

 if(setsockopt(server_fd,IPPROTO_IP,IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq))<0){
 perror("setsockopt");
exit(EXIT_FAILURE);
}
}

