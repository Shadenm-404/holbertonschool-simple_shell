#include "shell.h"

char *resolve_path(char *cmd)
{
    char *path = NULL;
    char **env = environ;
    char *copy, *dir;
    char full[512];

    if (!cmd)
        return (NULL);

    if (cmd[0] == '/' || cmd[0] == '.')
        return (strdup(cmd));

    while (*env)
    {
        if (strncmp(*env, "PATH=", 5) == 0)
        {
            path = *env + 5;
            break;
        }
        env++;
    }

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
