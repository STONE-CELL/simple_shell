#include "shell.h"

/**
 * _strcpy - Entry point
 * @dest: input
 * @src: input
 *
 * Return: Always 0
 */
char *_strcpy(char *dest, char *src)
{
	int o = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[o])
	{
		dest[o] = src[o];
		o++;
	}
	dest[o] = 0;
	return (dest);
}

/**
 * _strdup - Entry point
 * @str: input
 *
 * Return: Always 0
 */
char *_strdup(const char *str)
{
	int l = 0;
	char *t;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	t = malloc(sizeof(char) * (l + 1));
	if (!t)
		return (NULL);
	for (l++; l--;)
		t[l] = *--str;
	return (t);
}

/**
 * _puts - Entry point
 * @str: input
 *
 * Return: Always 0
 */
void _puts(char *str)
{
	int o = 0;

	if (!str)
		return;
	while (str[o] != '\0')
	{
		_putchar(str[o]);
		o++;
	}
}

/**
 * _putchar - Entry point
 * @c: input
 *
 * Return: On success 1, -1 if fails
 */
int _putchar(char c)
{
	static int o;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || o >= WRITE_BUF_SIZE)
	{
		write(1, buf, o);
		o = 0;
	}
	if (c != BUF_FLUSH)
		buf[o++] = c;
	return (1);
}


