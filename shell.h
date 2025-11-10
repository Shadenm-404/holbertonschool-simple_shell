#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* ===== Prompt & Tokenizing ===== */
#define PROMPT_TEXT "($) "
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/* ===== Shell state (used by builtins/exec) ===== */
typedef struct shell_state_s
{
	char *prog_name;          /* argv[0] */
	unsigned long line_count; /* number of read lines */
	int should_exit;          /* flag to exit REPL */
	int exit_status;          /* last/return status */
} shell_state_t;

/* ===== Builtins dispatch types ===== */
typedef int (*builtin_func)(char **args, shell_state_t *st);
typedef struct builtin_s
{
	char *name;
	builtin_func func;
} builtin_t;

/* ===== REPL modes (keep your current API) ===== */
void run_interactive(char **envp, const char *prog, int *last_code);
void run_noninteractive(char **envp, const char *prog, int *last_code);

/* ===== Optional unified loop API (if you use it) ===== */
int   sh_loop(shell_state_t *st);
char *sh_read_line(void);
char **sh_split_line(char *line);
int   sh_execute(char **args, shell_state_t *st);

/* ===== PATH resolution + execution (keep your names) ===== */
char *resolve_path(char *cmd);
int   execute_cmd(char *cmd, char **envp, const char *prog);

/* ===== Builtins ===== */
int builtin_dispatch(char **args, shell_state_t *st);
int bi_env(char **args, shell_state_t *st);
int bi_exit(char **args, shell_state_t *st);

/* ===== Utils ===== */
size_t _strlen(const char *s);
int    _strcmp(const char *s1, const char *s2);
char  *_strdup(const char *s);
int    _isdigit_str(const char *s);
int    _atoi_posmod(const char *s, int *out);
void   print_exit_illegal(shell_state_t *st, const char *arg);

#endif /* SHELL_H */
