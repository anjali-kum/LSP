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
int ip_convert(void);
// required for multicasting receiver
int sub_mc_mode(void);
int bind_sock(void);
// required for multicasting receiver

//int write_sock(void);
int read_sock(void);


struct sockaddr_in serv_addr,client_addr;
int sock = 0, msg_len,addrlen=sizeof(serv_addr);
char buffer[1024]={0};
char *hello = "Hello from client";
struct ip_mreq mreq;



int main(){

creat_sock();
ip_convert();
sub_mc_mode();
bind_sock();
while(1){
//multicast received; no need for write()
//write_sock();
read_sock();
}
close(sock);
return 0;
}



int creat_sock(void){
// creat a socket
if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0){
perror("socket creation failed");
exit(EXIT_FAILURE);
}

}

int ip_convert(void){

memset(&serv_addr,'\0',sizeof(serv_addr));
memset(&client_addr,'\0',sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
//serv_addr.sin_addr.s_addr = INADDR_ANY;
inet_pton(AF_INET, MULTICAST_GROUP, &serv_addr.sin_addr);

}


int sub_mc_mode(void){
// set the socket to multicast mode
mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
mreq.imr_interface.s_addr = htonl(INADDR_ANY);


 if(setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))<0){
 perror("setsockopt");
exit(EXIT_FAILURE);
}
}


int bind_sock(void){
 
 // Set the socket to allow multiple connections on the same port
 int opt =1;
 if(setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))<0){
 perror("setsockopt");
exit(EXIT_FAILURE);
}

//Bind the socket to a port
if(bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
perror("bind failed");
exit(EXIT_FAILURE);
}

}
/*
int write_sock(void){
printf("\n client::> ");
scanf("%s",buffer);
//send response to server
sendto(sock, (const char *)buffer, strlen(buffer),0,(const struct sockaddr *)&serv_addr, sizeof(serv_addr));
printf("\n");
}
*/

int read_sock(void){
memset(buffer,0,sizeof(buffer));
//Read data from server
msg_len = recvfrom(sock,(char *)buffer,1024,MSG_WAITALL, (struct sockaddr *)&serv_addr, &addrlen);
buffer[msg_len]='\0';
printf("Received: %s\n",buffer);
}



