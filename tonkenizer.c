#include "shell.h"

/**
 * tokenize - split a command line into tokens (arguments)
 * @line: input string from getline
 * Return: pointer to a NULL-terminated array of tokens
 */
char **tokenize(char *line)
{
	size_t cap = 8, i = 0;
	char **args = malloc(sizeof(char *) * cap);
	char *tok;

	if (!args)
		return (NULL);

	for (tok = strtok(line, " \t\r\n"); tok; tok = strtok(NULL, " \t\r\n"))
	{
		if (i + 1 >= cap)
		{
			cap *= 2;
			args = realloc(args, sizeof(char *) * cap);
			if (!args)
				return (NULL);
		}
		args[i++] = tok;
	}
	args[i] = NULL;
	return (args);
}
