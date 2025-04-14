#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

// Define the shared data structure
struct SharedData {
    sem_t semaphore;
    char message[100];
};

int main() {

    // Open the existing shared memory object
    int fd = shm_open("/my_shared_memory", O_RDWR, S_IRUSR | S_IWUSR);


    // Map the shared memory
    struct SharedData *shared_data = mmap(NULL, sizeof(struct SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Wait for the semaphore
    sem_wait(&shared_data->semaphore);

    // Display the user string
    printf("Server received: %s", shared_data->message);

    // Release the semaphore
    sem_post(&shared_data->semaphore);

    // Unmap the shared memory
    if (munmap(shared_data, sizeof(struct SharedData)) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor
    close(fd);

    return 0;
}

