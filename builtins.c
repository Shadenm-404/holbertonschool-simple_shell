#include <unistd.h>
#include "shell.h"

extern char **environ;

/**
 * builtin_env - prints current environment
 * @args: (unused)
 * @envp: (unused)
 * Return: 0 on success
 */
int builtin_env(char **args, char **envp)
{
    int i;

    (void)args;
    (void)envp;

    for (i = 0; environ[i] != NULL; i++)
    {
        write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}

int bi_exit(char **args, shell_state_t *st)
{
	int status = st->exit_status;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);

	if (args[1])
	{
		if (_isdigit_str(args[1]) && _atoi_posmod(args[1], &status) == 0)
		{
			st->should_exit = 1;
			st->exit_status = status;
			return (status);
		}
		print_exit_illegal(st, args[1]);
		return (2);
	}
	st->should_exit = 1;
	st->exit_status = status;
	return (status);
}

int builtin_dispatch(char **args, shell_state_t *st)
{
	int i;
	builtin_t table[] = {
		{"env", bi_env},
		{"exit", bi_exit},
		{NULL, NULL}
	};

	for (i = 0; table[i].name; i++)
	{
		if (_strcmp(args[0], table[i].name) == 0)
		{
			st->exit_status = table[i].func(args, st);
			return (1);
		}
	}
	return (0);
}

