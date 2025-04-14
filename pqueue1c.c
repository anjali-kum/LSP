// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MAX_MSG_SIZE 256
#define QUEUE_NAME "/my_queue"

int main() {
    mqd_t mq;
    char buffer[MAX_MSG_SIZE + 1];

    // Open the message queue for sending
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Client: Message Queue Opened\n");

    // Prompt user to enter a string
    printf("Enter a string to send to the server: ");
    fgets(buffer, MAX_MSG_SIZE, stdin);

    // Send the message to the server
    if (mq_send(mq, buffer, strlen(buffer), 0) == -1) {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }

    printf("Client: Message Sent to Server\n");

    // Close the message queue
    if (mq_close(mq) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    return 0;
}

