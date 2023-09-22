#include "shell.h"

/**
 * _erratoi - Entry point
 * @s:input
 * Return: 0 if passes, -1 on error
 *
 */
int _erratoi(char *s)
{
	int o = 0;
	unsigned long int r = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (o = 0;  s[o] != '\0'; o++)
	{
		if (s[o] >= '0' && s[o] <= '9')
		{
			r *= 10;
			r += (s[o] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (r);
}

/**
 * print_error - Entry point
 * @info:input
 * @estr:input
 * Return: 0 if passess, -1 if error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Entry point
 * @input: the input
 * @fd: input
 *
 * Return:Always 0
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int o, c = 0;
	unsigned int _abs_, t;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
	{
		_abs_ = input;
		t = _abs_;
	}
	for (o = 1000000000; o > 1; o /= 10)
	{
		if (_abs_ / o)
		{
			__putchar('0' + t / o);
			c++;
		}
		t %= o;
	}
	__putchar('0' + t);
	c++;

	return (c);
}

/**
 * convert_number - Entry point
 * @num: input
 * @base: input
 * @flags: input
 *
 * Return: Always 0
 */
char *convert_number(long int num, int base, int flags)
{
	static char *a;
	static char b[50];
	char s = 0;
	char *p;
	unsigned long m = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		s = '-';

	}
	a = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &b[49];
	*p = '\0';

	do	{
		*--p = a[m % base];
		m /= base;
	} while (m != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * remove_comments - Entry point
 * @buf: input
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int o;

	for (o = 0; buf[o] != '\0'; o++)
		if (buf[o] == '#' && (!o || buf[o - 1] == ' '))
		{
			buf[o] = '\0';
			break;
		}
}

