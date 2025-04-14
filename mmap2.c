#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

// Size of the shared memory region
#define data_size 100

int child(char *data){ // Child process (Server)
      int len;
        // Increment the shared data
        
        printf("Child process: enter the message\n");
        
        len =read(0,data,data_size-1);
        data[len]='\0';
        printf("Server process: Incremented shared data. Value: %s\n", data);

        // Unmap the shared memory
        if (munmap(data, data_size) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    } 
    
int parent(char *data){
int dummy;
 printf("give some number to read from shared\n");
 scanf("%d",&dummy);

        // Print the value of shared data
        printf("Client process: Shared data value after server execution: %s\n", data);

        // Unmap the shared memory
        if (munmap(data, data_size) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
        
        shm_unlink("/my_shared_memory");

}

int main() {
int op;
    // Create a named shared memory object
    int fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, data_size);

    // Map the shared memory
    char *shared_data = mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

 printf("enter your option:\n");
 printf("1 write \n");
 printf("2 read\n");
 scanf("%d",&op);
 
    if (op == 1) child(shared_data);
    
    else if(op == 2)  parent(shared_data);
    else{
    
 	printf("invalid input\n");
    }
    

        // Close and unlink the shared memory object
        close(fd);
    return 0;
}

