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

int main(){

int sock = 0, valread;
struct sockaddr_in serv_addr;;
char buffer[1024]={0};
char *message = "Hello from client";


// creat a socket
if((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
perror("socket creation failed");
exit(EXIT_FAILURE);
}

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

// Convert IPv4 and IPv6 address from text to binary form
if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr) <=0){
printf("\n Invalid address/ Address not supported \n");
exit(EXIT_FAILURE);
}

//connect to server
if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
printf("\n Connection failed \n");
exit(EXIT_FAILURE);
}

//send response to server
send(sock, message, strlen(message),0);
printf("hello message sent\n");


//Read data from server
valread = read(sock,buffer,1024);
printf("Server: %s\n",buffer);


return 0;
}



