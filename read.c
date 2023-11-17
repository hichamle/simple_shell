#include "shell.h"

void display_prompt() {
    printf(":) ");
    fflush(stdout);
}

void print_environment() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void execute_command(char *args[]) {
    // Fork a new process only if the command exists in the PATH
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
