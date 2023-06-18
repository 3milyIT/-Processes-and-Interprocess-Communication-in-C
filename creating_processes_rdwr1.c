#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    
    //tablica przechowująca deskryptory potoku (pipefd[o] - odczyt, pipefd[1] - zapis)
    int pipefd[2];
    //tworzymy zmienną do przechowywania identyfikatora
    pid_t pid;
    //tworzymy zmienną do przechowywania odczytywanych danych
    char buffer[100];
    
    //pipe() - utworzenie komunikacji między procesami
    
    //funkcja pipe przyjmuje tablicę pipefd i tworzy potok, przypisując odpowiednie deskryptory do jej elementów 
    //w przypadku błędu funkcja pipe() zwraca -1
    if(pipe(pipefd) == -1) {
        perror("Błąd tworzenia potoku");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    
    if(pid < 0) {
        perror("Błąd podczas forkowania");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0) {
        //zamknięcie końca odczytu
        close(pipefd[0]);
        const char* message = "HALLO!";
        
        //zapisanie napisu do potoku
        write(pipefd[1],message,100);
        //zamknięcie końca zapisu
        close(pipefd[1]);
        //oczekiwanie na zakończenie procesu potomnego
        wait(NULL);
    }
    else {
        //proces potomny
        close(pipefd[1]);
        
        read(pipefd[0],buffer,100);
        printf("Odczytano: %s\n",buffer);
        close(pipefd[0]);
        
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
