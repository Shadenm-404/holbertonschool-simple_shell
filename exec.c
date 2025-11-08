#include "shell.h"

int execute_cmd(char *cmd, char **envp, const char *prog)
{
    pid_t pid;
    int status;
    char *full;
    char *args[128];
    int i = 0;
    char *token;

    token = strtok(cmd, " \t");
    while (token != NULL && i < 127)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;

    if (args[0] == NULL)
        return (0);

    full = resolve_path(args[0]);
    if (full == NULL)
    {
        fprintf(stderr, "%s: command not found\n", prog);
        return (127);
    }

    pid = fork();
    if (pid == -1)
    {
        free(full);
        return (1);
    }

    if (pid == 0)
    {
        execve(full, args, envp);
        perror(prog);
        free(full);
        _exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(full);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}
