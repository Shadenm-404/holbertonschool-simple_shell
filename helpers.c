#include "shell.h"

/**
 * read_line - read a line from standard input
 *
 * Return: pointer to the line read, or NULL on failure or EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	characters = getline(&line, &bufsize, stdin);
	if (characters == -1)
	{
		free(line);
		return (NULL);
	}

	/* remove trailing newline */
	if (characters > 0 && line[characters - 1] == '\n')
	{
		line[characters - 1] = '\0';
	}

	return (line);
}

/**
 * _strlen - calculate the length of a string
 * @s: pointer to the string
 *
 * Return: length of the string, or 0 if NULL
 */
int _strlen(char *s)
{
	int len = 0;

	if (s == NULL)
	{
		return (0);
	}

	while (s[len] != '\0')
	{
		len++;
	}

	return (len);
}

/**
 * _strdup - duplicate a string
 * @str: pointer to the source string
 *
 * Return: pointer to duplicated string, or NULL on failure
 */
char *_strdup(char *str)
{
	char *dup;
	int len;
	int i;

	if (str == NULL)
	{
		return (NULL);
	}

	len = _strlen(str);
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
	{
		return (NULL);
	}

	for (i = 0; i <= len; i++)
	{
		dup[i] = str[i];
	}

	return (dup);
}

/**
 * _strcat - concatenate two strings
 * @dest: destination buffer
 * @src: source string to append
 *
 * Return: pointer to the destination string
 */
char *_strcat(char *dest, char *src)
{
	int dest_len;
	int i;

	if (dest == NULL || src == NULL)
	{
		return (dest);
	}

	dest_len = _strlen(dest);
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}

	dest[dest_len + i] = '\0';
	return (dest);
}

/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if equal, negative if s1 < s2, positive if s1 > s2,
 *         or -1 if either string is NULL
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (s1 == NULL || s2 == NULL)
	{
		return (-1);
	}

	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}

	return (s1[i] - s2[i]);
}
