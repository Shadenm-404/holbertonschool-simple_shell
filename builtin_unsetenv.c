#include "shell.h"

/**
 * _unsetenv - Remove an environment variable
 * @name: variable name
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
    int i, j;
    size_t len;

    if (!name)
        return (-1);

    len = strlen(name);
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            free(environ[i]);
            for (j = i; environ[j]; j++)
                environ[j] = environ[j + 1];
            return (0);
        }
    }
    return (0);
}
