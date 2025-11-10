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

char *find_in_path(const char *cmd)
{
	char *path, *dup, *dir, *full;
	size_t ld, lc;

	if (!cmd || !*cmd) return NULL;

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0) return _strdup(cmd);
		return NULL;
	}
	path = getenv("PATH");
	if (!path || !*path) return NULL;

	dup = _strdup(path);
	if (!dup) return NULL;

	lc = _strlen(cmd);
	dir = strtok(dup, ":");
	while (dir)
	{
		ld = _strlen(dir);
		full = malloc(ld + 1 + lc + 1);
		if (!full) { free(dup); return NULL; }
		memcpy(full, dir, ld); full[ld] = '/';
		memcpy(full + ld + 1, cmd, lc);
		full[ld + 1 + lc] = '\0';

		if (access(full, X_OK) == 0)
		{ free(dup); return full; }

		free(full);
		dir = strtok(NULL, ":");
	}
	free(dup);
	return NULL;
}
