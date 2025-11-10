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
/* Data Structures */
/**
 * struct builtin_s - Builtin command structure
 * @name: Name of the builtin command
 * @func: Function pointer to the builtin command function
 */
typedef struct builtin_s
{
	char *name;
	int (*func)(char **args, char **envp);
} builtin_t;
void interactive_mode(char **envp, char *program_name, int *last_status);
void non_interactive_mode(char **envp, char *program_name, int *last_status);
int process_command(char *command, char **envp, char *program_name);
int execute_command(char **args, char **envp, char *program_name);
char *find_command_path(char *command, char **envp);
void handle_execution_error(char *command, char *program_name);
int _atoi(char *str);
int execute_command(char **args, char **envp, char *program_name);
int handle_builtin_exit(char **args);
int fork_and_execute(char *command_path,
		char **args, char **envp, char *program_name);
char *find_command_path(char *command, char **envp);
int is_absolute_or_relative_path(char *command);
char *check_path(char *path);
char *search_path_directories(char **path_dirs, char *command);
void handle_execution_error(char *command, char *program_name);
char **parse_command(char *command);
void free_args(char **args);
char **split_path(char *path_env);
char **create_empty_path_array(void);
int process_path_tokens(char **path_dirs, char *path_env, int buffer_size);
int is_builtin(char *command);
int execute_builtin(char **args, char **envp);
int builtin_exit(char **args, char **envp);
int builtin_env(char **args, char **envp);
char *get_path_env(char **envp);
char **split_path(char *path_env);
char *build_command_path(char *directory, char *command);
char *read_line(void);
int _strlen(char *s);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
#endif /* SHELL_H */
