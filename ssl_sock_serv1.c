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
#include<openssl/ssl.h>
#include<openssl/err.h>

#define PORT 8080

//user defined functions
int creat_sock(void);
int set_sock(void);
int bind_sock(void);
int listen_sock(void);
int accept_sock(void);
//for SSL
int ssl_lib_init(void);
int ssl_accept_sock(void);
int read_sock(void);//modefied for SSL
int write_sock(void);//modefied for SSL
int ssl_end(void);


int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt =1;
int addrlen = sizeof(address);
char buffer[1024];
char *hello = "Hello from server123";

SSL_CTX *ctx;
SSL *ssl;


int main(){

ssl_lib_init();
creat_sock();
set_sock();
bind_sock();
listen_sock();
printf("server running\n");
accept_sock();
ssl_accept_sock();
read_sock();
write_sock();
ssl_end();

}


int ssl_lib_init(void){

    // SSL library initialization
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ctx = SSL_CTX_new(TLS_server_method());

    // Load server's certificate and private key
    if (SSL_CTX_use_certificate_file(ctx, "/home/ubuntu64/Desktop/Linux_System_Class/Program_13/server1.crt", SSL_FILETYPE_PEM) <= 0) {
            printf("Error: Unable to load server's certificate.\n");
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "/home/ubuntu64/Desktop/Linux_System_Class/Program_13/server1.key", SSL_FILETYPE_PEM) <= 0) {
        printf("Error: Unable to load server's private key.\n");
        exit(EXIT_FAILURE);
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

//Accepting Incomming connections
if((new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen))<0){
perror("accept");
exit(EXIT_FAILURE);
}

}


int ssl_accept_sock(void){
  // Create SSL session
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, new_socket);

    // Perform SSL handshake
    if (SSL_accept(ssl) <= 0) {
        printf("Error: SSL handshake failed.\n");
        ERR_print_errors_fp(stderr);
    }
}

int read_sock(void)
{

//Read data from client
//valread = read(new_socket,buffer,1024);
//SSL
valread = SSL_read(ssl,buffer,1024);

printf("client: %s\n",buffer);

}

int write_sock(void){

    write(1,"Server: ",sizeof("Server: "));
    valread = read(1, buffer, sizeof(buffer));
    buffer[valread] = '\0';
//write(new_socket, buffer, strlen(buffer));
//send response to client
SSL_write(ssl, buffer, strlen(buffer));
printf("hello message sent\n");

}


int ssl_end(void){
    // Close SSL session and free context
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    // Close the socket
    close(new_socket);
}

