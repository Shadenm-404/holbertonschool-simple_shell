#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"
#define PROMPT "$ "

void interactive_mode(char **envp, char *program_name, int *last_status);
void non_interactive_mode(char **envp, char *program_name, int *last_status);
int process_command(char *command, char **envp, char *program_name);

#endif
