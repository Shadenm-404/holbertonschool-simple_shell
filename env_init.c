#include "shell.h"
static int env_owned = 0;
static size_t my_strlen(const char *s)
{
    size_t n = 0;
    if (!s) return 0;
    while (s[n]) n++;
    return n;
}

static char *my_strdup_local(const char *s)
{
    size_t len = my_strlen(s);
    char *p = malloc(len + 1);
    size_t i;

    if (!p) return NULL;
    for (i = 0; i < len; i++) p[i] = s[i];
    p[len] = '\0';
    return p;
}

/**
 * init_env - duplicate envp into a writable environ we own
 * @envp: environment from main
 * Return: 0 on success, -1 on failure
 */
int init_env(char **envp)
{
    size_t count = 0, i;
    char **copy;

    if (!envp)
        return (0);

    while (envp[count])
        count++;

    copy = malloc(sizeof(char *) * (count + 1));
    if (!copy)
        return (-1);

    for (i = 0; i < count; i++)
    {
        copy[i] = my_strdup_local(envp[i]);
        if (!copy[i])
        {
            size_t j;
            for (j = 0; j < i; j++)
                free(copy[j]);
            free(copy);
            return (-1);
        }
    }
	copy[count] = NULL;

	environ = copy;
	_env_mark_owned();
    return (0);
}

void _env_mark_owned(void)
{
    env_owned = 1;
}

void free_env(void)
{
    size_t i;

    if (!env_owned || !environ)
        return;

    for (i = 0; environ[i]; i++)
        free(environ[i]);

    free(environ);
    environ = NULL;
    env_owned = 0;
}
