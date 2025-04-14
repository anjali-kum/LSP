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


//user defined functions
int creat_sock(void);
int ip_convert(void);
int serv_connect(void);
int write_sock(void);
int read_sock(void);

int unblock_socket(void);

int sock = 0, valread;
int flags;
struct sockaddr_in serv_addr;;
char buffer[1024]={0};
//char hello[1023] = "Hello from client";



int main(){

creat_sock();
ip_convert();
unblock_socket();
serv_connect();
//wait for connection to complete (1sec)
sleep(1);

while(1){
write_sock();
while(read_sock());

printf("//----------------received-------------//\n");
}
return 0;
}



int creat_sock(void){
// creat a socket
if((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
perror("socket creation failed");
exit(EXIT_FAILURE);
}

}

int ip_convert(void){
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

// Convert IPv4 and IPv6 address from text to binary form
if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr) <=0){
printf("\n Invalid address/ Address not supported \n");
exit(EXIT_FAILURE);
}
}

int serv_connect(void){
// non blocking
while(1){
//connect to server
if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
//printf("\n Connection failed \n");
//exit(EXIT_FAILURE);
continue;
}
else break;
}

}


int write_sock(void){

printf("Request ::> ");
scanf("%s",buffer);
//send response to client
send(sock, buffer, strlen(buffer),0);
sleep(1);
printf("sent ::> %s\n",buffer);
if(strcmp(buffer,"exit")==0)exit(0);
memset(buffer,'\0',sizeof(buffer));
}


int read_sock(void){
//Read data from client
valread=0;
valread = read(sock,buffer,1024);
if(valread>0){
printf("Server Response: %s\n",buffer);
if(strcmp(buffer,"exit")==0)exit(0);
memset(buffer,'\0',sizeof(buffer));
return 0;
}

else {
write(1,"no data yet...\n",strlen("no data yet...\n"));
sleep(1);
 return 1;
}

}



int unblock_socket(void){
flags=fcntl(sock,F_GETFL,0);
fcntl(sock,F_SETFL,flags | O_NONBLOCK);
}
