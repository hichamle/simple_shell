#include "shell.h"

int main(void) {
    char *line;
    char **args;
    int status;

    signal(SIGINT, handle_signal); // Handle Ctrl+C

    do {
        printf("($) ");
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free_args(args);
    } while (status);

    return EXIT_SUCCESS;
}
