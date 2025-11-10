#include "shell.h"

int execute_cmd(char *cmd, char **envp, const char *prog)
{
	pid_t pid;
	int status;
	char *full;
	char *args[128];
	int i = 0;
	char *token;

	token = strtok(cmd, " \t");
	while (token != NULL && i < 127)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return (0);

	/* exit builtin MUST run before PATH */
	if (strcmp(args[0], "exit") == 0)
		return (-1000);

	/* env builtin */
	if (strcmp(args[0], "env") == 0)
	{
		int j = 0;

		while (environ[j])
		{
			write(STDOUT_FILENO, environ[j], strlen(environ[j]));
			write(STDOUT_FILENO, "\n", 1);
			j++;
		}
		return (0);
	}

	full = resolve_path(args[0]);
	if (full == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		free(full);
		return (1);
	}

	if (pid == 0)
	{
		execve(full, args, envp);
		perror(prog);
		free(full);
		_exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free(full);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}


int run_external(char **args, shell_state_t *st)
{
	pid_t pid;
	int status = 0;
	char *path = find_in_path(args[0]);

	if (!path)
	{
		dprintf(STDERR_FILENO, "%s: %lu: %s: not found\n",
			st->prog_name, st->line_count, args[0]);
		st->exit_status = 127;
		return 127;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return errno;
	}
	if (pid == 0)
	{
		execve(path, args, environ);
		perror("execve");
		free(path);
		_exit(126);
	}
	free(path);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return errno;
	}
	if (WIFEXITED(status))
		st->exit_status = WEXITSTATUS(status);
	else
		st->exit_status = 128;

	return st->exit_status;
}
