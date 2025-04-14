#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8080

// User defined functions
int create_sock(void);
int ip_convert(void);
int serv_connect(void);
int ssl_lib_init(void);
int ssl_serv_connect(void);
int read_sock(void);  // Modified for SSL
int write_sock(void); // Modified for SSL
int ssl_end(void);

int sock = 0, valread;
struct sockaddr_in serv_addr;
char buffer[1024];

SSL_CTX *ctx;
SSL *ssl;

int main() {

    ssl_lib_init();
    create_sock();
    ip_convert();
    serv_connect();
    ssl_serv_connect();
    write_sock();
    sleep(1);
    read_sock();
    ssl_end();

    return 0;
}

int ssl_lib_init(void) {
    // SSL library initialization
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ctx = SSL_CTX_new(TLS_client_method());  // Use TLS_client_method() for the client

    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    printf("SSL library initialized.\n");
}

int create_sock(void) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created.\n");
}

int ip_convert(void) {
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n Invalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
    printf("Server address converted.\n");
}

int serv_connect(void) {
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Connection failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server.\n");
}

int ssl_serv_connect(void) {
    // Create SSL session
    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    SSL_set_fd(ssl, sock);

    // Perform SSL handshake
    if (SSL_connect(ssl) <= 0) {
        printf("Error: SSL handshake failed.\n");
        ERR_print_errors_fp(stderr);
        return -1;
    }
    printf("SSL handshake successful.\n");
}

int write_sock(void) {
    write(1,"Client: ",sizeof("Client: "));
    valread = read(1, buffer, sizeof(buffer));
    buffer[valread] = '\0';
    // Send data to the server using SSL
    SSL_write(ssl, buffer, strlen(buffer));
    printf("Data sent to server.\n");
}

int read_sock(void) {
    // Read data from the server using SSL
    valread = SSL_read(ssl, buffer, sizeof(buffer));
    buffer[valread] = '\0';
    printf("Server: %s\n", buffer);
}

int ssl_end(void) {
    // Close SSL session and free context
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    // Close the socket
    close(sock);
    printf("SSL session ended and socket closed.\n");
}

