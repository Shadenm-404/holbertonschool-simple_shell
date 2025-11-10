#include "shell.h"

/**
 * execute_command - execute a command by forking and execve
 * @args: array of argument strings
 * @envp: array of environment variable strings
 * @program_name: name of the shell executable
 *
 * Return: exit status of the command
 */
int execute_command(char **args, char **envp, char *program_name)
{
	int status;
	char *command_path;

	if (args == NULL || args[0] == NULL)
		return (0);

	if (handle_builtin_exit(args))
		return (0);

	command_path = find_command_path(args[0], envp);
	if (command_path == NULL)
	{
		handle_execution_error(args[0], program_name);
		return (127);
	}

	status = fork_and_execute(command_path, args, envp, program_name);
	free(command_path);
	return (status);
}

/**
 * handle_builtin_exit - handle exit builtin command
 * @args: array of argument strings
 *
 * Return: 1 if exit was handled, 0 otherwise
 */
int handle_builtin_exit(char **args)
{
	int exit_status = 0;

	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
			exit_status = _atoi(args[1]);
		free_args(args);
		exit(exit_status);
	}
	return (0);
}

/**
 * fork_and_execute - fork process and execute command
 * @command_path: full path to command
 * @args: array of argument strings
 * @envp: array of environment variables
 * @program_name: name of shell executable
 *
 * Return: exit status of command
 */
int fork_and_execute(char *command_path, char **args,
		char **envp, char *program_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(command_path, args, envp) == -1)
		{
			handle_execution_error(args[0], program_name);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (status);
}

/**
 * find_command_path - find the full path of a command
 * @command: command to locate
 * @envp: array of environment variable strings
 *
 * Return: allocated string of command path, or NULL if not found
 */
char *find_command_path(char *command, char **envp)
{
	char *path_env, **path_dirs, *command_path;

	if (command == NULL)
		return (NULL);

	if (is_absolute_or_relative_path(command))
		return (check_path(command));

	path_env = get_path_env(envp);
	if (path_env == NULL || path_env[0] == '\0')
	{
		free(path_env);
		return (NULL);
	}

	path_dirs = split_path(path_env);
	free(path_env);
	if (path_dirs == NULL)
		return (NULL);

	command_path = search_path_directories(path_dirs, command);
	free_args(path_dirs);
	return (command_path);
}

/**
 * is_absolute_or_relative_path - check if command has path
 * @command: command to check
 *
 * Return: 1 if absolute/relative path, 0 otherwise
 */
int is_absolute_or_relative_path(char *command)
{
	return (command[0] == '/' || command[0] == '.');
}
