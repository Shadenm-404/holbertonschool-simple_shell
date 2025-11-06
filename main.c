#include "shell.h"

#define MAX_ARGS 128

/**
 * fetch_input - Reads one line from stdin and strips trailing newline.
 *
 * Return: malloc'ed string on success (must be freed by caller),
 *         or NULL on EOF/error.
 */
static char *fetch_input(void)
{
	char *buf = NULL;
	size_t cap = 0;
	ssize_t nread;

	nread = getline(&buf, &cap, stdin);
	if (nread == -1)
	{
		free(buf);
		return (NULL);
	}
	if (nread > 0 && buf[nread - 1] == '\n')
		buf[nread - 1] = '\0';
	return (buf);
}

/**
 * trim_ws - Trims leading/trailing spaces/tabs in-place.
 * @s: string to trim (modified in-place).
 */
static void trim_ws(char *s)
{
	char *start, *end;
	size_t len;

	if (s == NULL)
		return;

	start = s;
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
	{
		s[0] = '\0';
		return;
	}

	len = strlen(start);
	end = start + (len - 1);
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';

	if (start != s)
		memmove(s, start, strlen(start) + 1);
}

/**
 * is_empty_line - Checks if a string is empty (after trimming) or NULL.
 * @txt: input string.
 *
 * Return: 1 if empty/NULL, 0 otherwise.
 */
static int is_empty_line(const char *txt)
{
	if (txt == NULL)
		return (1);
	while (*txt == ' ' || *txt == '\t')
		txt++;
	return (*txt == '\0');
}

/**
 * make_argv - Tokenizes a line into argv by spaces/tabs.
 * @line: input line (will be modified by strtok).
 *
 * Return: newly allocated array of pointers (argv). Caller must free it with
 *         free_argv(). Note: tokens point inside @line, do not free them.
 */
static char **make_argv(char *line)
{
	char **argv;
	char *tok;
	int i;

	if (line == NULL)
		return (NULL);

	argv = (char **)malloc((MAX_ARGS + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);

	i = 0;
	tok = strtok(line, " \t");
	while (tok != NULL && i < MAX_ARGS)
	{
		argv[i] = tok;
		i++;
		tok = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * free_argv - Frees argv array created by make_argv().
 * @argv: argv to free (tokens themselves must NOT be freed).
 */
static void free_argv(char **argv)
{
	if (argv != NULL)
		free(argv);
}

/**
 * execute_simple - Executes a command (argv[0]) with arguments, no PATH search.
 * @cmd: raw command line (will be tokenized; modified in-place).
 * @envp: environment variables array.
 * @prog: shell program name (for perror prefix).
 *
 * Return: child's exit status (0..255), or 1 on wait error, 127 on exec error.
 */
int execute_simple(char *cmd, char **envp, const char *prog)
{
	pid_t pid;
	int status, st;
	char **argv_exec;

	argv_exec = make_argv(cmd);
	if (argv_exec == NULL || argv_exec[0] == NULL)
	{
		free_argv(argv_exec);
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		free_argv(argv_exec);
		return (1);
	}

	if (pid == 0)
	{
		execve(argv_exec[0], argv_exec, envp);
		perror(prog);
		_exit(127);
	}

	st = 0;
	status = 0;
	if (waitpid(pid, &st, 0) == -1)
	{
		perror(prog);
		status = 1;
	}
	else if (WIFEXITED(st))
	{
		status = WEXITSTATUS(st);
	}
	else
	{
		status = 1;
	}

	free_argv(argv_exec);
	return (status);
}

/**
 * run_interactive - Runs the shell in interactive mode (prints prompt).
 * @envp: environment variables array.
 * @prog: shell program name (argv[0]).
 * @last_code: out parameter for last exit status.
 */
void run_interactive(char **envp, const char *prog, int *last_code)
{
	char *line;

	for (;;)
	{
		write(STDOUT_FILENO, PROMPT_TEXT, (unsigned int)strlen(PROMPT_TEXT));

		line = fetch_input();
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		trim_ws(line);
		if (!is_empty_line(line))
			*last_code = execute_simple(line, envp, prog);

		free(line);
	}
}

/**
 * run_noninteractive - Runs the shell in non-interactive mode (no prompt).
 * @envp: environment variables array.
 * @prog: shell program name (argv[0]).
 * @last_code: out parameter for last exit status.
 */
void run_noninteractive(char **envp, const char *prog, int *last_code)
{
	char *line;

	while ((line = fetch_input()) != NULL)
	{
		trim_ws(line);
		if (!is_empty_line(line))
			*last_code = execute_simple(line, envp, prog);
		free(line);
	}
}

/**
 * main - Entry point.
 * @argc: argument count.
 * @argv: argument vector.
 * @envp: environment variables array.
 *
 * Return: last command's exit status.
 */
int main(int argc, char **argv, char **envp)
{
	int last_status;

	last_status = 0;
	(void)argc;

	if (isatty(STDIN_FILENO))
		run_interactive(envp, argv[0], &last_status);
	else
		run_noninteractive(envp, argv[0], &last_status);

	return (last_status);
}
