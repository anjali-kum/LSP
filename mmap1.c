#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define data_size 100


int child(char *data);

int parent(char *data);

int main() {

    // Create a shared memory region
    char *shared_data = mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();    // Fork a child process

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) child(shared_data);// Child process
    else parent(shared_data); // Parent process
        
       // Unmap the shared memory
        if (munmap(shared_data, data_size) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }    

    return 0;
}

int child(char *data){
int len;
char local_data[data_size];

        printf("Child process: enter the message\n");
        
               /* method 1
        
        len =read(0,local_data,data_size-1);
        local_data[len]='\0';
        strcpy(data,local_data);
        
      // */ 
      
      //  /*method 2
        len =read(0,data,data_size-1);
        data[len]='\0';
    //    */


}
int parent(char *data){
// Wait for the child to finish
        wait(NULL);

        printf("Parent process: message from child is\n");
        // Print the value of shared data
        printf("%s\n", data);

 
}

