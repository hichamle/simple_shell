#include "shell.h"

char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **split_line(char *line) {
    const char *delimiter = " \t\r\n\a";
    char **tokens = malloc(BUFSIZE * sizeof(char *));
    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char *token = strtok(line, delimiter);
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, delimiter);
    }
    tokens[i] = NULL;
    return tokens;
}

int execute(char **args) {
    pid_t pid, wpid;
    int status;

    if (args[0] == NULL) {
        return 1;  // Empty command
    }

    if (check_builtin(args)) {
        return 1;  // Builtin command executed
    }

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execve(args[0], args, NULL) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int check_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        free_args(args);
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "env") == 0) {
        // Implement env
        char **env = environ;
        while (*env) {
            printf("%s\n", *env++);
        }
        return 1;
    }

    return 0;  // Not a builtin command
}

char *find_path(char *command) {
    // Implement PATH handling
    // You can use strtok to tokenize the PATH variable and check each directory
    // to see if the command exists in that directory.
    // Return the full path if found, NULL otherwise.
}

void handle_signal(int signo) {
    // Handle signals, for example, Ctrl+C (SIGINT)
    printf("\n");
}

void free_args(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}
