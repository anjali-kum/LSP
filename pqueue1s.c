// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MAX_MSG_SIZE 256
#define QUEUE_NAME "/my_queue"

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_MSG_SIZE + 1];

    // Set message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;        // Maximum number of messages in the queue
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Open the message queue for receiving
    mq = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Server: Message Queue Opened\n");

    // Server will keep running and waiting for messages
    while (1) {
        // Receive a message from the queue
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_MSG_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the received message
        buffer[bytes_read] = '\0';

        // Display the received message
        printf("Server: Received Message: %s\n", buffer);	
        
        if(strcmp(buffer,"exit\n")==0){
       	 printf("Server terminated\n");
       	 
       	     // Close the message queue
	    if (mq_close(mq) == -1) {
	        perror("mq_close");
	        exit(EXIT_FAILURE);
	    }

	    // Unlink the message queue
	    if (mq_unlink(QUEUE_NAME) == -1) {
	        perror("mq_unlink");
	        exit(EXIT_FAILURE);
	    }

	return 0;
	}
    }


    return 0;
}

