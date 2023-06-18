#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    
    char* fifoName = "newFifo";
    mkfifo(fifoName, 0666);
    
    pid_t pid;
    char buffer[100];
    
    pid = fork();
    
    if (pid < 0) {
        perror("Error forking process");
        exit(1);
    }
    else if (pid > 0) {
        // Parent process
        scanf("%s", buffer);
        
        // Open the named pipe in write mode
        int fd = open(fifoName, O_WRONLY);
        
        // Write the data to the named pipe
        write(fd, buffer, sizeof(buffer));
        
        close(fd);
        
        wait(NULL);
    }
    else {
        // Child process
        // Open the named pipe in read mode
        int fd = open(fifoName, O_RDONLY);
        
        // Read from the named pipe
        read(fd, buffer, sizeof(buffer));
        printf("Received message: %s", buffer);
        
        close(fd);
    }
    
    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    
    char* fifoName = "newFifo";
    mkfifo(fifoName,0666);
    
    pid_t pid;
    char buffer[100];
    
    pid = fork();
    
    if(pid < 0) {
        perror("Błąd podczas forkowania");
        exit(1);
    }
    else if(pid > 0) {
        //proces macierzysty
        scanf("%s",buffer);
        int fd = open(fifoName, O_WRONLY);
        write(fd,buffer,sizeof(buffer));
        close(fd);
        wait(NULL);
    }
    else {
        int fd = open(fifoName,O_RDONLY);
        read(fd,buffer,sizeof(buffer));
        printf("Received message: %s",buffer);
        close(fd);
    }
    
    return 0;
}
