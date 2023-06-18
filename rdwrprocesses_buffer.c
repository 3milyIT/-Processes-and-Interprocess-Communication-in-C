
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    
    if(pipe(pipefd) == -1) {
        perror("Błąd tworzenia potoku");
        exit(1);
    }
    
    pid = fork();
    
    if(pid < 0) {
        perror("Błąd podczas forkowania");
        exit(1);
    }
    else if(pid > 0) {
        //proces macierzysty
        close(pipefd[0]);
        scanf("%s",buffer);
        write(pipefd[1],buffer,100);
        wait(NULL);
    }
    else {
				//proces potomny
        close(pipefd[1]);
        read(pipefd[0],buffer,100);
        printf("Received message: %s",buffer);
    }
    
    return 0;
}


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
        exit(1);
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Error forking process");
        exit(1);
    }
    else if (pid > 0) {
        // Parent process
        close(pipefd[0]);
        
        scanf("%s", buffer);
        printf("Input: %s\n", buffer);
        
        // Write the data to the pipe using standard output
        printf("%s", buffer);
        
        close(pipefd[1]);
        
        wait(NULL);
    }
    else {
        // Child process
        close(pipefd[1]);
        
        // Read from the pipe using standard input
        scanf("%s", buffer);
        printf("Received message: %s", buffer);
        
        close(pipefd[0]);
    }
    
    return 0;
}
