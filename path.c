#include "shell.h"
/**
 * get_path_env - get value of PATH environment variable
 * @envp: array of environment variable strings
 *
 * Return: allocated string containing PATH value, or empty string if not found
 */
char *get_path_env(char **envp)
{
	int i;
	char *path_prefix = "PATH=";
	int prefix_len = 5;

	if (envp == NULL)
	{
		return (_strdup(""));
	}

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], path_prefix, prefix_len) == 0)
		{
			return (_strdup(envp[i] + prefix_len));
		}
	}

	/* return empty string if PATH not found */
	return (_strdup(""));
}
/**
 * split_path - splits PATH environment variable into directories
 * @path_env: PATH environment variable string
 *
 * Return: array of directory strings, NULL on failure
 */
char **split_path(char *path_env)
{
	char **path_dirs;
	int i = 0;
	int buffer_size = BUFFER_SIZE;

	if (path_env == NULL)
		return (NULL);

	if (path_env[0] == '\0')
		return (create_empty_path_array());

	path_dirs = malloc(buffer_size * sizeof(char *));
	if (path_dirs == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	i = process_path_tokens(path_dirs, path_env, buffer_size);
	if (i < 0)
		return (NULL);

	path_dirs[i] = NULL;
	return (path_dirs);
}

/**
 * create_empty_path_array - creates empty path array
 *
 * Return: array with single NULL element, NULL on malloc failure
 */
char **create_empty_path_array(void)
{
	char **path_dirs = malloc(sizeof(char *));

	if (path_dirs == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	path_dirs[0] = NULL;
	return (path_dirs);
}

/**
 * process_path_tokens - processes and stores path tokens
 * @path_dirs: array to store directories
 * @path_env: PATH environment variable
 * @buffer_size: initial buffer size
 *
 * Return: final index on success, -1 on failure
 */
int process_path_tokens(char **path_dirs, char *path_env, int buffer_size)
{
	char *token;
	int i = 0;

	token = strtok(path_env, ":");
	while (token != NULL)
	{
		path_dirs[i] = _strdup(token);
		if (path_dirs[i] == NULL)
		{
			perror("strdup");
			free_args(path_dirs);
			return (-1);
		}

		i++;
		if (i >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			path_dirs = realloc(path_dirs, buffer_size * sizeof(char *));
			if (path_dirs == NULL)
			{
				perror("realloc");
				return (-1);
			}
		}
		token = strtok(NULL, ":");
	}
	return (i);
}
/**
 * build_command_path - build full path for a command in directory
 * @directory: directory path string
 * @command: command name string
 *
 * Return: allocated string of full command path, or NULL on failure
 */
char *build_command_path(char *directory, char *command)
{
	char *command_path;
	int dir_len;
	int cmd_len;

	if (directory == NULL || command == NULL)
	{
		return (NULL);
	}

	dir_len = _strlen(directory);
	cmd_len = _strlen(command);

	command_path = malloc(dir_len + cmd_len + 2);
	if (command_path == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	strcpy(command_path, directory);
	command_path[dir_len] = '/';
	strcpy(command_path + dir_len + 1, command);

	return (command_path);
}
