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
int len;

    // Open or create a shared memory object
    int fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(struct SharedData));

    // Map the shared memory
    struct SharedData *shared_data = mmap(NULL, sizeof(struct SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore (process shared)
    sem_init(&shared_data->semaphore, 1, 1);

    // Wait for the semaphore
    sem_wait(&shared_data->semaphore);

    // Get user input
    write(1,"Enter a string: ",strlen("Enter a string: "));
    len = read(0,shared_data->message, sizeof(shared_data->message)-1);
    shared_data->message[len]='\0';
    
    // Release the semaphore
    sem_post(&shared_data->semaphore);
    
    printf("String: %s\nis loaded to shared memory\n",shared_data->message);
    scanf("%d",&len);

    // Unmap the shared memory
    if (munmap(shared_data, sizeof(struct SharedData)) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Close and unlink the shared memory object
    close(fd);
    shm_unlink("/my_shared_memory");

    return 0;
}

