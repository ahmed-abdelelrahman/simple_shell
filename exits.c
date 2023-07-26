#include "shell.h"

/**
 * exit_shell - Exit the shell
 * @info: The parameter & return info struct
 * Return: The exit status
 */
int exit_shell(info_t *info)
{
	return (info->status);
}

/**
 * _atoi - Converts a string to an integer
 * @s: The string to be converted
 * Return: The converted integer if successful, -1 on error
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	unsigned int result = 0;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result * sign);
}

/**
 * _env - Print the environment
 * @info: The parameter & return info struct
 * Return: Always return 0
 */
int _env(__attribute__((unused)) info_t *info)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
		_puts(environ[i]);

	return (0);
}
