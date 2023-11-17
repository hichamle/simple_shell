#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

        // Check for built-in commands
        if (args[0] != NULL && strcmp(args[0], "exit") == 0) {
            printf("Goodbye!\n");
            exit(EXIT_SUCCESS);
        } else if (args[0] != NULL && strcmp(args[0], "env") == 0) {
            print_environment();
        } else if (args[0] != NULL) {
            execute_command(args);
        }
    }

    return 0;
}
