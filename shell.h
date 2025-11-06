#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT_TEXT "#cisfun$ "

extern char **environ;

void run_interactive(char **envp, const char *prog, int *last_code);
void run_noninteractive(char **envp, const char *prog, int *last_code);
int  execute_simple(char *cmd, char **envp, const char *prog);

#endif /* SHELL_H */

