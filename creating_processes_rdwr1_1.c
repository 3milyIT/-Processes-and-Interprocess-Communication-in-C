#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    
    if (pipe(pipefd) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {
        // Parent process
        close(pipefd[0]);
        const char* message = "HALLO!";
        
        // Write the message to the pipe
        write(pipefd[1], message, 100);
        
        close(pipefd[1]);
        wait(NULL);
    }
    else {
        // Child process
        close(pipefd[1]);
        
        // Read from the pipe
        read(pipefd[0], buffer, 100);
        printf("Received: %s\n", buffer);
        
        close(pipefd[0]);
        
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
