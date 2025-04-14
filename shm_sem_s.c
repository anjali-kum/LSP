#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_SIZE 1024
#define SEM_KEY 1234


union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


int main() {
int len;
struct sembuf sop;



    // Create a key for the semaphore and shared memory
    key_t key = ftok(".", SEM_KEY);

    // Create a semaphore 
    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    
    // initial semaphore with value 0
    union semun sem_arg;
    sem_arg.val = 0;
    semctl(sem_id, 0, SETVAL, sem_arg);

    // Create or get a shared memory segment
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    // Attach to the shared memory segment
    char *shm_addr = (char *)shmat(shm_id, NULL, 0);
	
	//Decrement semaphore to wait for the client to increment
	printf("Server waiting for client...\n");
	sop.sem_num = 0; // semaphore array index 0
	sop.sem_op = -1; // decrement by -1 operation
	sop.sem_flg = 0; // no flag
    if (semop(sem_id, &sop, 1) == -1) {
        perror("semop");
        exit(1);
    }
    
  
    // Client has incremented the semaphore after loading the string
    printf("Server received data from client: %s\n", shm_addr);

    // Reverse the string
    int length = strlen(shm_addr);
    for (int i = 0; i < length / 2; i++) {
        char temp = shm_addr[i];
        shm_addr[i] = shm_addr[length - i - 1];
        shm_addr[length - i - 1] = temp;
    }

    printf("Server reversed the string: %s\n", shm_addr);

    // incrementing the semaphore to release the client after processing the string 
	sop.sem_op = 1; // increment by 1 operation
    if (semop(sem_id, &sop, 1) == -1) {
        perror("semop");
        exit(1);
    }

    // Delay
    sleep(1);
    
    printf("Server waiting for client to complete...\n");

//Decrement semaphore to wait for the client to increment
	sop.sem_op = -1; // decrement by -1 operation
    if (semop(sem_id, &sop, 1) == -1) {
        perror("semop");
        exit(1);
    }
    
    // Detach from shared memory
    shmdt(shm_addr);

    // Remove shared memory segment and semaphore
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);

    printf("Server closed\n");
    return 0;
}

