#include "shell.h"

/**
 * _unsetenv - Remove an environment variable
 * @name: variable name (must not contain '=' and not be empty)
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	if (!name || !*name || strchr(name, '='))
		return (-1);

	return (unsetenv(name));
}
