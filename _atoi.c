#include "shell.h"

/**
 * interactive - Entry point
 * @info:input
 *
 * Return: 1 if pass , 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Entry point
 * @c: input
 * @delim: input
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Entry point
 * @c:input
 * Return: 1 if c true, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Entry point
 * @s:input
 * Return: 0 if no numbers in string
 */

int _atoi(char *s)
{
	int o, n = 1, g = 0, t;
	unsigned int r = 0;

	for (o = 0; s[o] != '\0' && g != 2; o++)
	{
		if (s[o] == '-')
			n *= -1;

		if (s[o] >= '0' && s[o] <= '9')
		{
			g = 1;
			r *= 10;
			r += (s[o] - '0');
		}
		else if (g == 1)
			g = 2;
	}

	if (n == -1)
		t = -r;
	else
		t = r;

	return (t);
}

