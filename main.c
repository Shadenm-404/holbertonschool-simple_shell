#include "shell.h"

static int exit_code = 0;

/**
* fetch_input - Reads a full line of input from standard input
* Return: Pointer to the read string on success, or NULL on EOF
*/
static char *fetch_input(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t chars = getline(&buffer, &bufsize, stdin);

if (chars == -1)
{
free(buffer);
return NULL;
}
if (chars > 0 && buffer[chars - 1] == '\n')
buffer[chars - 1] = '\0';
return buffer;
}

/**
* is_empty_line - Checks if the given string is empty or whitespace
* @txt: Pointer to the input string
* Return: 1 if the line is empty or whitespace only, 0 ow
*/
static int is_empty_line(const char *txt)
{
if (!txt)
return (1);

while (*txt == ' ' || *txt == '\t')
txt++;

return (*txt == '\0');
}

/**
* run_interactive - Runs the shell in interactive mode
* @envp: Environment variables array
* @prog: Name of the shell executable
* @last_code: Pointer to an integer holding the last exit status
* Return: nothing
*/
void run_interactive(char **envp, const char *prog, int *last_code)
{
char *user_cmd;

while (1)
{
write(STDOUT_FILENO, PROMPT_TEXT, strlen(PROMPT_TEXT));
user_cmd = fetch_input();

f (!user_cmd)
{
write(STDOUT_FILENO, "\n", 1);
break;
}

if (!is_empty_line(user_cmd))
*last_code = execute_simple(user_cmd, envp, prog);

free(user_cmd);
}
}

/**
* run_interactive - Runs the shell in noninteractive mode
* @envp: Environment variables array.
* @prog: Name of the shell executable.
* @last_code: Pointer to an integer holding the last exit status.
* Return: nothing
*/
void run_noninteractive(char **envp, const char *prog, int *last_code)
{
char *user_cmd;

while ((user_cmd = fetch_input()) != NULL)
{
if (!is_empty_line(user_cmd))
*last_code = execute_simple(user_cmd, envp, prog);

free(user_cmd);
}
}

/**
* execute_simple - Executes a single command without arguments or PATH
* @cmd: The command to execute
* @envp: Environment variables array
* @prog: Name of the shell executable
* Return: Exit status of the executed command
*/
int execute_simple(char *cmd, char **envp, const char *prog)
{
pid_t child_pid = fork();
int temp_status = 0;

if (child_pid == -1)
{
perror(prog);
return 1;
}

if (child_pid == 0)
{
char *cmd_argv[2] = { cmd, NULL };
execve(cmd_argv[0], cmd_argv, envp);
perror(prog);
_exit(127);
}
else {
int wait_status;
if (waitpid(child_pid, &wait_status, 0) == -1)
perror(prog);
else if (WIFEXITED(wait_status))
temp_status = WEXITSTATUS(wait_status);
else
temp_status = 1;

exit_code = temp_status;
return temp_status;
}
}

/**
* main - Entry point of the simple shell program
* @argc: Argument count
* @argv: Argument vector
* @envp: Environment variable array
* Return: The last command’s exit status
*/
int main(int argc, char **argv, char **envp)
{
int current_status = 0;
(void)argc;

if (isatty(STDIN_FILENO))
run_interactive(envp, argv[0], &current_status);
else
run_noninteractive(envp, argv[0], &current_status);

return current_status;
}
