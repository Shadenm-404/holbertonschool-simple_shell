#include <unistd.h>
#include "shell.h"

extern char **environ;

/**
 * builtin_env - prints current environment
 * @args: (unused)
 * @envp: (unused)
 * Return: 0 on success
 */
int builtin_env(char **args, char **envp)
{
    int i;

    (void)args;
    (void)envp;

    for (i = 0; environ[i] != NULL; i++)
    {
        write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}
