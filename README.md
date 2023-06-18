# -Processes-and-Interprocess-Communication-in-C

#### ***Creating Processes and Interprocess Communication in C***

### Method 1: Using Pipes

The first method utilizes pipes for interprocess communication. Pipes provide a communication channel between two processes, where one process writes data to the pipe, and the other process reads from it. In C, the `pipe()` function is used to create a pipe, and `write()` and `read()` functions are used to write and read data from the pipe, respectively.

In the first program, two processes are created - the parent process and the child process - using the `fork()` function. The parent process writes the message "HALLO!" to the pipe using the `write()` function, and the child process reads the message from the pipe using the `read()` function.

The C program code using pipes can be written as follows:

```c
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
```

### Method 2: Using Standard Input/Output

Another method of interprocess communication is using standard input/output. In this case, one process writes data to the standard output, and the other process reads from the standard input. In C programs, the `printf()` and `scanf()` functions are used to write and read data using standard input/output.

In the second program, two processes are created - the parent process and the child process - using the `fork()` function. The parent process reads data from the standard input using `scanf()` and writes it to the pipe using standard output. The child process reads data from the pipe using standard input and prints the received messages using `printf()`.

The C program code using standard input/output can be written as follows:

```c
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
```

### Extension of Method 1: Using Named Pipes

As an extension to the first method, named pipes can be used for interprocess communication. Named pipes, also known as FIFOs, provide a way for processes to communicate by reading and writing to a special file in the file system. In C, the `mkfifo()` function is used to create a named pipe, and `open()`, `write()`, and `read()` functions are used to interact with the named pipe.

In the extended program, a named pipe is created using the `mkfifo()` function. The parent process writes data to the named pipe using `write()`, and the child process reads the data from the named pipe using `read()` and prints the received message.

The C program code using named pipes can be written as follows:

```c
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
```

These methods provide different approaches to achieve interprocess communication in C programs. The choice of method depends on the specific requirements and context in which the program is being used.




.

## Tworzenie procesów i komunikacja między nimi w języku C

W języku C istnieje wiele metod tworzenia procesów i komunikowania się między nimi. Przedstawione poniżej programy demonstrują trzy różne podejścia: wykorzystanie potoków (pipe), standardowego wejścia/wyjścia oraz połączeń nazwanych (mkfifo). Pozwól mi przedstawić każdą z tych metod w interesujący sposób.

### Metoda 1: Wykorzystanie potoków (pipe)

Potoki (pipe) są popularnym mechanizmem komunikacji między procesami w systemach Unix. W języku C można tworzyć potoki za pomocą funkcji `pipe()`, która tworzy połączenie między dwoma procesami - procesem macierzystym i procesem potomnym.

Potok składa się z dwóch końców: końca odczytu i końca zapisu. Dane zapisane do jednego końca mogą być odczytane z drugiego końca. 

W pierwszym programie tworzony jest potok przy użyciu funkcji `pipe()`. Deskryptory potoku (pipefd[0] - końcówka do odczytu, pipefd[1] - końcówka do zapisu) przechowywane są w tablicy `pipefd`. Następnie proces macierzysty i potomny są tworzone za pomocą funkcji `fork()`. Proces macierzysty zapisuje napis "HALLO!" do potoku przy użyciu funkcji `write()`, a proces potomny odczytuje ten napis z potoku przy użyciu funkcji `read()`. 

Kod programu w języku C, wykorzystujący potoki, może wyglądać następująco:

```c
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
        perror("Błąd tworzenia potoku");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Błąd podczas forkowania");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {
        // Zamknięcie końca odczytu
        close(pipefd[0]);
        const char* message = "HALLO!";
        
        // Zapisanie napisu do potoku
        write(pipefd[1], message, 100);
        
        // Zamknięcie końca zapisu
        close(pipefd[1]);
        
        // Oczekiwanie na zakończenie procesu potomnego
        wait(NULL);
    }
    else {
        // Proces potomny
        close(pipefd[1]);
        
        read(pipefd[0], buffer, 100);
        printf("Odczytano: %s\n", buffer);
        
        close(pipefd[0]);
        
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
```

###

 Metoda 2: Wykorzystanie standardowego wejścia/wyjścia

Innym sposobem komunikacji między procesami jest wykorzystanie standardowego wejścia/wyjścia. W tym przypadku, jeden z procesów zapisuje dane do standardowego wyjścia, a drugi odczytuje je z standardowego wejścia. W przypadku programów w języku C, funkcje `printf()` i `scanf()` są używane do zapisu i odczytu danych za pomocą standardowego wejścia/wyjścia.

W drugim programie tworzone są dwa procesy - proces macierzysty i proces potomny - za pomocą funkcji `fork()`. Proces macierzysty odczytuje dane ze standardowego wejścia za pomocą funkcji `scanf()` i zapisuje je do potoku przy użyciu standardowego wyjścia. Proces potomny odczytuje dane z potoku przy użyciu standardowego wejścia za pomocą funkcji `scanf()` i drukuje otrzymane komunikaty przy użyciu funkcji `printf()`.

Kod programu w języku C, wykorzystujący standardowe wejście/wyjście, może wyglądać następująco:

```c
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
        perror("Błąd tworzenia potoku");
        exit(1);
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Błąd podczas forkowania");
        exit(1);
    }
    else if (pid > 0) {
        // Proces macierzysty
        close(pipefd[0]);
        
        scanf("%s", buffer);
        printf("Wpisano: %s\n", buffer);
        
        // Zapisanie danych do potoku za pomocą standardowego wyjścia
        printf("%s", buffer);
        
        close(pipefd[1]);
        
        wait(NULL);
    }
    else {
        // Proces potomny
        close(pipefd[1]);
        
        // Odczytanie danych z potoku za pomocą standardowego wejścia
        scanf("%s", buffer);
        
        printf("Otrzymano: %s\n", buffer);
        
        close(pipefd[0]);
    }
    
    return 0;
}
```

### Metoda 3: Wykorzystanie połączeń nazwanych (mkfifo)

Trzecim sposobem komunikacji między procesami jest wykorzystanie połączeń nazwanych, które są reprezentowane przez specjalne pliki w systemie operacyjnym. W języku C, funkcja `mkfifo()` służy do utworzenia połączenia nazwanego.

W trzecim programie używamy funkcji `mkfifo()` do utworzenia połączenia nazwanego. Po utworzeniu połączenia, tworzone są dwa procesy - proces macierzysty i proces potomny - za pomocą funkcji `fork()`. Pro

ces macierzysty odczytuje dane ze standardowego wejścia za pomocą funkcji `scanf()` i zapisuje je do połączenia nazwanego przy użyciu funkcji `write()`. Proces potomny odczytuje dane z połączenia nazwanego przy użyciu funkcji `read()` i drukuje otrzymane komunikaty.

Kod programu w języku C, wykorzystujący połączenia nazwane, może wyglądać następująco:

```c
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
        perror("Błąd podczas forkowania");
        exit(1);
    }
    else if (pid > 0) {
        // Proces macierzysty
        scanf("%s", buffer);
        
        // Otwarcie połączenia nazwanego w trybie zapisu
        int fd = open(fifoName, O_WRONLY);
        
        // Zapisanie danych do połączenia nazwanego
        write(fd, buffer, sizeof(buffer));
        
        close(fd);
        
        wait(NULL);
    }
    else {
        // Proces potomny
        // Otwarcie połączenia nazwanego w trybie odczytu
        int fd = open(fifoName, O_RDONLY);
        
        // Odczytanie danych z połączenia nazwanego
        read(fd, buffer, sizeof(buffer));
        
        printf("Otrzymano wiadomość: %s", buffer);
        
        close(fd);
    }
    
    return 0;
}
```

Metody przedstawione powyżej umożliwiają komunikację między procesami w języku C. Można je wykorzystać w zależności od konkretnych wymagań i preferencji. Wybór odpowiedniej metody zależy od specyfiki programu i kontekstu, w którym jest stosowany.
