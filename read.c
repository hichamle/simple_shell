#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt() {
    printf("#cisfun$ ");
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

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(input, input, (char *)NULL);

            // If exec fails, print an error
            perror("exec");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            // Check if the child process terminated successfully
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                fprintf(stderr, "./shell: %s: No such file or directory\n", input);
            }
        }
    }

    return 0;
}
