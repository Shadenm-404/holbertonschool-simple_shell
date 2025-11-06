#include "shell.h"

/**
 * fetch_input - Reads one line from stdin; trims trailing newline.
 * Return: malloc'ed string or NULL on EOF/error.
 */
static char *fetch_input(void)
{
    char *buf = NULL;
    size_t cap = 0;
    ssize_t n = getline(&buf, &cap, stdin);

    if (n == -1) {
        free(buf);
        return NULL;
    }
    if (n > 0 && buf[n - 1] == '\n')
        buf[n - 1] = '\0';
    return buf;
}

/**
 * is_empty_line - Checks if string is empty or only spaces/tabs.
 * @txt: input string
 * Return: 1 if empty/whitespace-only, else 0.
 */
static int is_empty_line(const char *txt)
{
    if (!txt) return 1;
    while (*txt == ' ' || *txt == '\t')
        txt++;
    return (*txt == '\0');
}

/**
 * execute_simple - Executes a single command (no args, no PATH).
 * @cmd: command path (e.g. /bin/ls)
 * @envp: env
 * @prog: program name for perror prefix
 * Return: exit status of child (0..255), 1 on wait error, 127 on exec error.
 */
int execute_simple(char *cmd, char **envp, const char *prog)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1) {
        perror(prog);
        return 1;
    }

    if (pid == 0) {
        char *argv_exec[2] = { cmd, NULL };
        execve(argv_exec[0], argv_exec, envp);
        perror(prog);
        _exit(127);
    }

    /* parent */
    {
        int st;
        if (waitpid(pid, &st, 0) == -1) {
            perror(prog);
            status = 1;
        } else if (WIFEXITED(st)) {
            status = WEXITSTATUS(st);
        } else {
            status = 1;
        }
    }
    return status;
}

/**
 * run_interactive - Interactive loop with prompt.
 * @envp: env
 * @prog: program name
 * @last_code: last exit status out param
 */
void run_interactive(char **envp, const char *prog, int *last_code)
{
    char *line;

    for (;;) {
        write(STDOUT_FILENO, PROMPT_TEXT, (unsigned int)strlen(PROMPT_TEXT));

        line = fetch_input();
        if (!line) { /* Ctrl+D */
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (!is_empty_line(line))
            *last_code = execute_simple(line, envp, prog);

        free(line);
    }
}

/**
 * run_noninteractive - Reads commands from stdin without prompt.
 * @envp: env
 * @prog: program name
 * @last_code: last exit status out param
 */
void run_noninteractive(char **envp, const char *prog, int *last_code)
{
    char *line;

    while ((line = fetch_input()) != NULL) {
        if (!is_empty_line(line))
            *last_code = execute_simple(line, envp, prog);
        free(line);
    }
}

/**
 * main - Entry point
 */
int main(int argc, char **argv, char **envp)
{
    int last_status = 0;
    (void)argc;

    if (isatty(STDIN_FILENO))
        run_interactive(envp, argv[0], &last_status);
    else
        run_noninteractive(envp, argv[0], &last_status);

    return last_status;
}
