
#include "shell.h"
/**
 * check_path - check if path exists and is executable
 * @path: path to check
 *
 * Return: duplicated path if valid, NULL otherwise
 */
char *check_path(char *path)
{
	struct stat st;

	if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
		return (_strdup(path));
	return (NULL);
}

/**
 * search_path_directories - search PATH directories for command
 * @path_dirs: array of PATH directories
 * @command: command to search for
 *
 * Return: full path if found, NULL otherwise
 */
char *search_path_directories(char **path_dirs, char *command)
{
	int i;
	char *command_path;
	struct stat st;

	for (i = 0; path_dirs[i] != NULL; i++)
	{
		command_path = build_command_path(path_dirs[i], command);
		if (command_path == NULL)
			continue;
		if (stat(command_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (command_path);
		free(command_path);
	}
	return (NULL);
}

/**
 * handle_execution_error - print error message for failed command
 * @command: command that failed
 * @program_name: name of the shell executable
 */
void handle_execution_error(char *command, char *program_name)
{
	char error_message[BUFFER_SIZE];
	int len;

	len = snprintf(error_message, BUFFER_SIZE,
			"%s: 1: %s: not found\n",
			program_name, command);
	write(STDERR_FILENO, error_message, len);
}

