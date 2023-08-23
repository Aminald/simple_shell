#include "shell.h"

int main(void) {
    run_shell();
    return 0;
}

void run_shell(void) {
    // Your main code implementation here
    // ...
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char buffer[BUFFER_SIZE];
    char *prompt = "#cisfun$ ";
    ssize_t read_bytes;
    
    while (1)
    {
        printf("%s", prompt);
        
        read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (read_bytes == 0) // Ctrl+D (EOF) handling
        {
            printf("\n");
            break;
        }
        else if (read_bytes == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        buffer[read_bytes - 1] = '\0'; // Remove the newline character
        
        if (strcmp(buffer, "exit") == 0) // Exit the shell
            break;
        
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            if (execve(buffer, NULL, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            wait(NULL);
        }
    }
    
    return 0;
}

