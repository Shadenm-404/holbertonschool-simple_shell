#include "shell.h"

/**
 * _atoi - convert a string to an integer
 * @str: pointer to the string to convert
 *
 * Return: integer value represented by str
 */
int _atoi(char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			break;
		}
		result = result * 10 + (str[i] - '0');
	}

	return (sign * result);
}
