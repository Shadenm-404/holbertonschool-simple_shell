#include "shell.h"

/**
 * is_builtin - check if command is a built-in command
 * @command: pointer to the command string
 *
 * Return: 1 if command is built-in, 0 otherwise
 */
int is_builtin(char *command)
{
	if (!command)
		return (0);

	if (_strcmp(command, "exit") == 0)
		return (1);
	if (_strcmp(command, "env") == 0)
		return (1);
	if (_strcmp(command, "setenv") == 0)
		return (1);
	if (_strcmp(command, "unsetenv") == 0)
		return (1);

	return (0);
}

/**
 * execute_builtin - execute a built-in command
 * @args: array of argument strings
 * @envp: array of environment variable strings
 *
 * Return: exit status of the built-in command
 */
int execute_builtin(char **args, char **envp)
{
	(void)envp;

	if (_strcmp(args[0], "env") == 0)
	{
		size_t i;

		for (i = 0; environ[i]; i++)
		{
			write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (0);
	}
	else if (_strcmp(args[0], "setenv") == 0)
	{
		if (!args[1] || !args[2])
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (1);
		}
		if (_setenv(args[1], args[2], 1) != 0)
			fprintf(stderr, "setenv: Failed to set variable\n");
		return (0);
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		if (!args[1])
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (1);
		}
		if (_unsetenv(args[1]) != 0)
			fprintf(stderr, "unsetenv: Failed to unset variable\n");
		return (0);
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		return (0);
	}

	return (0);
}

/**
 * builtin_exit - handle the exit built-in command
 * @args: array of argument strings (ignored)
 * @envp: array of environment variable strings (ignored)
 *
 * Return: exit status 0
 */
int builtin_exit(char **args, char **envp)
{
	(void)args;
	(void)envp;

	return (0);
}

/**
 * builtin_env - handle the env built-in command
 * @args: array of argument strings (ignored)
 * @envp: array of environment variable strings
 *
 * Return: 0 on success
 */
int builtin_env(char **args, char **envp)
{
	int i;

	(void)args;

	if (envp == NULL)
	{
		return (0);
	}

	for (i = 0; envp[i] != NULL; i++)
	{
		write(STDOUT_FILENO, envp[i], _strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * handle_builtin - checks and executes builtin shell commands
 * @args: array of command arguments, where args[0] is the command name
 *Return:
 * 1 if a builtin command was executed successfully or handled,
 * 0 if the command is not a builtin.
 */
int handle_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		if (!args[1] || !args[2])
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (1);
		}
		if (_setenv(args[1], args[2], 1) != 0)
			fprintf(stderr, "setenv: Failed to set variable\n");
		return (1);
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		if (!args[1])
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (1);
		}
		if (_unsetenv(args[1]) != 0)
			fprintf(stderr, "unsetenv: Failed to unset variable\n");
		return (1);
	}
	return (0); /* Not a builtin */
}
