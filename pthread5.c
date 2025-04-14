#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

sem_t *sem; //POSIX semaphore pointer

int main() {

int x; // dummy variable for execution control
    // Create or open the semaphore with a unique name, initial value, and appropriate permissions
   // sem = sem_open("/my_semaphore", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
    sem = sem_open("/my_semaphore", O_CREAT , S_IRUSR | S_IWUSR, 1);

    if (sem == SEM_FAILED) {
        perror("Semaphore creation/opening failed");
        exit(EXIT_FAILURE);
    }

    // Process A
    printf("give input to start Process A critical section\n");   scanf("%d",&x);
    
    sem_wait(sem);
    printf("Process A in critical section\n");
    
    printf("give input to release semaphore \n");    scanf("%d",&x);
    sem_post(sem);

    // Process B
    printf("give input to start Process B critical section\n");   scanf("%d",&x);
    sem_wait(sem);
    printf("Process B in critical section\n");
    
    printf("give input to release semaphore \n");    scanf("%d",&x);
    sem_post(sem);

    // Close the semaphore
    sem_close(sem);

    // Optionally unlink the semaphore (remove it from the system)
    sem_unlink("/my_semaphore");

    return 0;
}

