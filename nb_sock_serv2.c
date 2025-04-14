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
int set_sock(void);
int bind_sock(void);
int listen_sock(void);
int accept_sock(void);
int read_sock(void);
int write_sock(void);

int unblock_socket(void);


int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt =1;
int addrlen = sizeof(address);
int flags;
char buffer[1024]={0};
char *hello = "Hello from server";


int main(){

	creat_sock();
//	set_sock();
	bind_sock();
	unblock_socket();
	listen_sock();
	accept_sock();
	while(1){
		while(read_sock());
		write_sock();
		}	
		
	}



int creat_sock(void){

// creat a socket
if((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
perror("socket failed");
exit(EXIT_FAILURE);
}

}

int set_sock(void){

//Set socket option 
if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
perror("setsockopt");
exit(EXIT_FAILURE);
}

}

int bind_sock(void){

address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);

//Bind the socket to a port
if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
perror("bind failed");
exit(EXIT_FAILURE);
}

}

int listen_sock(void){

//Listen for Incomming connections
if(listen(server_fd,3)<0){
perror("listen");
exit(EXIT_FAILURE);
}

}

int accept_sock(void){
//kept in while loop to continiously poll for incomming connecctions
while(1){
//Accepting Incomming connections
if((new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen))<0){
//perror("accept");
//exit(EXIT_FAILURE);
sleep(2); //wait for a connection (2 sec)
continue;
}
else{
return 1;
}
}
}

int read_sock(void)
{

//Read data from client
valread=0;

//while(valread==0){
//Read data from client

if((valread = read(new_socket,buffer,1024))>0){
buffer[valread]='\0';
printf("client Request: %s\n",buffer);
if(strcmp(buffer,"exit")==0)exit(0);
return 0;
}

else{
write(1,"no data yet...\n",sizeof("no data yet...\n")-1);
sleep(1);
 return 1;
}

}

int write_sock(void){

printf("Response ::> ");
scanf("%s",buffer);
//send response to client
send(new_socket, buffer, strlen(buffer),0);
sleep(1);
printf("//----------------sent-------------//\n");
if(strcmp(buffer,"exit")==0) exit(0);
memset(buffer,'\0',sizeof(buffer));

}


int unblock_socket(void){
flags=fcntl(new_socket,F_GETFL,0);
fcntl(server_fd,F_SETFL,flags | O_NONBLOCK);
}

