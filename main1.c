#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Final exit status from the shell loop
 */
int main(int ac, char **av)
{
	shell_state_t st;
	(void)ac;

	st.prog_name = av[0];
	st.line_count = 0;
	st.should_exit = 0;
	st.exit_status = 0;

	return (sh_loop(&st));
}

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
