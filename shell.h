#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define BUFFER_SIZE 1024
#define TOKEN_DELIM "\t\r\n\a"
#define PROMPT "$"

void run_noninteractive(char **envp, const char *prog, int *last_code)
void run_interactive(char **envp, const char *prog, int *last_code)
int execute_simple(char *cmd, char **envp, const char *prog)

#endif
