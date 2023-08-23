#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

int main(void)
{
    char input[MAX_INPUT_LENGTH];
    char *args[2]; // We only expect one argument (the command)

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) // Read user input
        {
            printf("\n");
            break; // Handle Ctrl+D (EOF)
        }

        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (strcmp(input, "exit") == 0) // Exit the shell
            break;

        args[0] = input;
        args[1] = NULL; // Terminate the args array

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Child process
        {
            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        else // Parent process
        {
            int status;
            waitpid(pid, &status, 0); // Wait for child to finish
        }
    }

    return 0;
}
