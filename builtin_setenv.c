#include "shell.h"

/**
 * _setenv - Initialize or modify an environment variable
 * @name: variable name (must not contain '=' and not be empty)
 * @value: variable value (must not be NULL)
 * @overwrite: if 0, keep existing; if non-zero, overwrite
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	if (!name || !*name || strchr(name, '=') || !value)
		return (-1);

	if (!overwrite)
	{
		char *old = getenv(name);

		if (old != NULL)
			return (0);
	}
	return (setenv(name, value, 1));
}
