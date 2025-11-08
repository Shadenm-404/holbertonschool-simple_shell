#include "shell.h"

#define MAX_ARGS 128

static char *fetch_input(void)
{
	char *buf = NULL;
	size_t cap = 0;
	ssize_t nread;

	nread = getline(&buf, &cap, stdin);
	if (nread == -1)
	{
		free(buf);
		return (NULL);
	}
	if (nread > 0 && buf[nread - 1] == '\n')
		buf[nread - 1] = '\0';
	return (buf);
}

static void trim_ws(char *s)
{
	char *start, *end;
	size_t len;

	if (s == NULL)
		return;

	start = s;
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
	{
		s[0] = '\0';
		return;
	}

	len = strlen(start);
	end = start + (len - 1);
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';

	if (start != s)
		memmove(s, start, strlen(start) + 1);
}

static int is_empty_line(const char *txt)
{
	if (txt == NULL)
		return (1);
	while (*txt == ' ' || *txt == '\t')
		txt++;
	return (*txt == '\0');
}

void run_interactive(char **envp, const char *prog, int *last_code)
{
	char *line;

	for (;;)
	{
		write(STDOUT_FILENO, PROMPT_TEXT, (unsigned int)strlen(PROMPT_TEXT));

		line = fetch_input();
		if (line == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		trim_ws(line);
		if (!is_empty_line(line))
			*last_code = execute_cmd(line, envp, prog);

		free(line);
	}
}

void run_noninteractive(char **envp, const char *prog, int *last_code)
{
	char *line;

	while ((line = fetch_input()) != NULL)
	{
		trim_ws(line);
		if (!is_empty_line(line))
			*last_code = execute_cmd(line, envp, prog);
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	int last_status;

	last_status = 0;
	(void)argc;

	if (isatty(STDIN_FILENO))
		run_interactive(envp, argv[0], &last_status);
	else
		run_noninteractive(envp, argv[0], &last_status);

	return (last_status);
}
