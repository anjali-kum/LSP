#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_SIZE 1024
#define SEM_KEY 1234


int main() {

int len;
struct sembuf sop;


    // Create a key for the semaphore and shared memory
    key_t key = ftok(".", SEM_KEY);


    // Check & get if the shared memory segment is available
    int shm_id = shmget(key, SHM_SIZE, 0);
    if (shm_id == -1) {
        perror("Server not started. Terminating...\n");
        exit(1);
    }
    
    // Get the semaphore created by the server
    int sem_id = semget(key, 1, 0);

    // Attach to the shared memory segment
    char *shm_addr = (char *)shmat(shm_id, NULL, 0);


        // Get user input & lod in shared memory
        write(1,"Shared memory available. Enter a string: ",strlen("Shared memory available. Enter a string: "));
       len= read(0,shm_addr, 100);
        shm_addr[len] = '\0'; 
        
        
        // incrementing the semaphore to release server 
        	sop.sem_num = 0; // semaphore array index 0
	sop.sem_op = 1; // increment by 1 operation
	sop.sem_flg = 0; // no flag
    if (semop(sem_id, &sop, 1) == -1) {
        perror("semop");
        exit(1);
    }
               

        // Delay 
        sleep(1);

        //  decrementing the semaphore --> Wait for server process
	sop.sem_op = -1; // decrement by -1 operation
    if (semop(sem_id, &sop, 1) == -1) {
        perror("semop");
        exit(1);
    }
        

        // Print the string --> should be reversed
        printf("Client received reversed string: %s\n", shm_addr);



        // Detach from shared memory
        shmdt(shm_addr);
        
                //incrementing the semaphore to release the server
	sop.sem_op = 1; // increment by 1 operation
    if (semop(sem_id, &sop, 1) == -1) {
        perror("semop");
        exit(1);
    }

    

    return 0;
}

