#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void display_prompt() {
    printf(":) ");
    fflush(stdout);
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        display_prompt();

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character
        input[strcspn(input, "\n")] = '\0';

        // Tokenize the input into command and arguments
        char *args[MAX_ARGS];
        size_t arg_count = 0;

        // Tokenize the input using space as a delimiter
        char *token = strtok(input, " ");
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }

        // Null-terminate the array
        args[arg_count] = NULL;

        // Fork a new process only if the command exists in the PATH
        if (args[0] != NULL) {
            // Fork a new process
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                execvp(args[0], args);

                // If exec fails, print an error
                perror("exec");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                int status;
                waitpid(pid, &status, 0);

                // Check if the child process terminated successfully
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    fprintf(stderr, ":) %s: command not found\n", args[0]);
                }
            }
        }
    }

    return 0;
}
