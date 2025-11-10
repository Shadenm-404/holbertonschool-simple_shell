/* utils.c */
#include "shell.h"

size_t _strlen(const char *s) { size_t n = 0; if (!s) return 0; while (s[n]) n++; return n; }

int _strcmp(const char *s1, const char *s2)
{ while (*s1 && *s2 && *s1 == *s2) { s1++; s2++; } return ((unsigned char)*s1 - (unsigned char)*s2); }

char *_strdup(const char *s)
{
	size_t n, i; char *p;
	if (!s) return NULL; n = _strlen(s);
	p = malloc(n + 1); if (!p) return NULL;
	for (i = 0; i < n; i++) p[i] = s[i];
	p[n] = '\0'; return p;
}

int _isdigit_str(const char *s)
{
	size_t i = 0;
	if (!s || !*s) return 0;
	if (s[0] == '+') i = 1;
	for (; s[i]; i++) if (s[i] < '0' || s[i] > '9') return 0;
	return 1;
}

int _atoi_posmod(const char *s, int *out)
{
	unsigned long v = 0; size_t i = 0;
	if (!s || !out) return 1;
	if (s[0] == '+') i = 1;
	for (; s[i]; i++) v = v * 10 + (unsigned long)(s[i] - '0');
	*out = (int)(v & 0xFF);
	return 0;
}

void print_exit_illegal(shell_state_t *st, const char *arg)
{
	dprintf(STDERR_FILENO, "%s: %lu: exit: Illegal number: %s\n",
		st->prog_name, st->line_count, arg);
}
