#include "shell.h"

/**
 * _eputs - Entry point
 * @str: input
 *
 * Return:Always 0
 */
void _eputs(char *str)
{
	int o = 0;

	if (!str)
		return;
	while (str[o] != '\0')
	{
		_eputchar(str[o]);
		o++;
	}
}

/**
 * _eputchar - Entry point
 * @c:input
 *
 * Return: On success 1, -1 if fails
 */
int _eputchar(char c)
{
	static int o;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || o >= WRITE_BUF_SIZE)
	{
		write(2, buf, o);
		o = 0;
	}
	if (c != BUF_FLUSH)
		buf[o++] = c;
	return (1);
}

/**
 * _putfd - Entry point
 * @c: input
 * @fd: input
 *
 * Return: On success 1, -1 if fails
 */
int _putfd(char c, int fd)
{
	static int o;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || o >= WRITE_BUF_SIZE)
	{
		write(fd, buf, o);
		o = 0;
	}
	if (c != BUF_FLUSH)
		buf[o++] = c;
	return (1);
}

/**
 * _putsfd - Entry point
 * @str:input
 * @fd:input
 *
 * Return:always 0
 */
int _putsfd(char *str, int fd)
{
	int o = 0;

	if (!str)
		return (0);
	while (*str)
	{
		o += _putfd(*str++, fd);
	}
	return (o);
}

