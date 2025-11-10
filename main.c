#include "shell.h"

#define MAX_ARGS 128

void run_interactive(char **envp, const char *prog, int *last_code)
{
	char *line;
	int code;

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
		{
			code = execute_cmd(line, envp, prog);
			if (code == -1000)
			{
				free(line);
				break;
			}
			*last_code = code;
		}

		free(line);
	}
}

void run_noninteractive(char **envp, const char *prog, int *last_code)
{
	char *line;
	int code;

	while ((line = fetch_input()) != NULL)
	{
		trim_ws(line);
		if (!is_empty_line(line))
		{
			code = execute_cmd(line, envp, prog);
			if (code == -1000)
			{
				free(line);
				break;
			}
			*last_code = code;
		}
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	int last_status = 0;
	(void)argc;

	if (isatty(STDIN_FILENO))
		run_interactive(envp, argv[0], &last_status);
	else
		run_noninteractive(envp, argv[0], &last_status);

	return (last_status);
}
