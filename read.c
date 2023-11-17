#include "shell.h"

char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **split_line(char *line) {
    // Implementation...
}

int execute(char **args) {
    // Implementation...
}

void free_args(char **args) {
    // Implementation...
}
