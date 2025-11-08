#include "shell.h"

/**
 * resolve_path - search PATH directories for a command
 * @cmd: command name
 *
 * Return: newly allocated string with full path, or NULL if not found
 */
char *resolve_path(char *cmd)
{
    char *path, *copy, *dir;
    char full[512];

    if (!cmd)
        return (NULL);

    /* if absolute or relative path already */
    if (cmd[0] == '/' || cmd[0] == '.')
        return (strdup(cmd));

    path = getenv("PATH");
    if (!path)
        return (NULL);

    copy = strdup(path);
    dir = strtok(copy, ":");

    while (dir)
    {
        snprintf(full, sizeof(full), "%s/%s", dir, cmd);
        if (access(full, X_OK) == 0)
        {
            free(copy);
            return (strdup(full));
        }
        dir = strtok(NULL, ":");
    }

    free(copy);
    return (NULL);
}
