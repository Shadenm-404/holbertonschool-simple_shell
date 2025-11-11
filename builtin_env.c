#include "shell.h"

/**
 * print_env - prints the current environment to STDOUT
 */
void print_env(void)
{
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
