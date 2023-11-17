#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define BUFSIZE 1024

/* Function Prototypes */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int check_builtin(char **args);
char *find_path(char *command);
void handle_signal(int signo);
void free_args(char **args);

#endif /* SHELL_H */
