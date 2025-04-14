#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEM_KEY 1234

union semun {
    int val;
    struct semid_ds *buf;
   unsigned short *array;
};

int sem_id;


void lock(void);// Function to lock (decrement) the semaphore
void unlock(void);// Function to unlock (increment) the semaphore

int main() {

    int option = 5;
    // Create or get a semaphore with an initial value of 0
    key_t key = ftok(".", SEM_KEY);
    sem_id = semget(key, 1, IPC_CREAT | 0666);

    union semun sem_arg;
    sem_arg.val = 0;

    semctl(sem_id, 0, SETVAL, sem_arg);


    do {
        // Ask the user to select an option
        printf("Select an option:\n");
        printf("1. Lock\n");
        printf("2. Unlock\n");
        printf("0. Quit\n");
        printf("Option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                lock();
                break;
            case 2:
                unlock();
                break;
            case 0:
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

    // Remove the semaphore
    semctl(sem_id, 0, IPC_RMID);

    return 0;
}

void lock(void) {
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1; // Decrement by 1
    sem_op.sem_flg = 0;


    printf("Locking now\n");
    // Attempt to lock the semaphore
    if (semop(sem_id, &sem_op, 1) == -1) {
        perror("lock");
        exit(EXIT_FAILURE);
    }
    printf("Unlocked now\n");

}


void unlock(void) {
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = 1; // Increment by 1
    sem_op.sem_flg = 0;

    // Unlock the semaphore
    if (semop(sem_id, &sem_op, 1) == -1) {
        perror("unlock");
        exit(EXIT_FAILURE);
    }

    printf("Unlocked now\n");
}

