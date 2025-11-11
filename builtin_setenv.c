#include "shell.h"

/**
 * _setenv - Initialize or modify an environment variable
 * @name: variable name
 * @value: variable value
 * @overwrite: 1 to overwrite existing variable, 0 to keep
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    int i;
    size_t len;

    if (!name || !value)
        return (-1);

    len = strlen(name);
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            if (!overwrite)
                return (0);
            /* Replace existing variable */
            free(environ[i]);
            environ[i] = malloc(len + strlen(value) + 2);
            if (!environ[i])
                return (-1);
            sprintf(environ[i], "%s=%s", name, value);
            return (0);
        }
    }

    /* Add new variable */
    environ = realloc(environ, sizeof(char *) * (i + 2));
    if (!environ)
        return (-1);
    environ[i] = malloc(len + strlen(value) + 2);
    if (!environ[i])
        return (-1);
    sprintf(environ[i], "%s=%s", name, value);
    environ[i + 1] = NULL;

    return (0);
}
