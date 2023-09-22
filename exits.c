#include "shell.h"

/**
 **_strncpy - Entry point
 *@dest: input
 *@src: input
 *@n:input
 *Return: Always 0
 */
char *_strncpy(char *dest, char *src, int n)
{
	int o, k;
	char *r = dest;

	o = 0;
	while (src[o] != '\0' && o < n - 1)
	{
		dest[o] = src[o];
		o++;
	}
	if (o < n)
	{
		k = o;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (r);
}

/**
 **_strncat - Entry point
 *@dest: input
 *@src: input
 *@n: input
 *Return: Always 0
 */
char *_strncat(char *dest, char *src, int n)
{
	int o, k;
	char *r = dest;

	o = 0;
	k = 0;
	while (dest[o] != '\0')
		o++;
	while (src[k] != '\0' && k < n)
	{
		dest[o] = src[k];
		o++;
		k++;
	}
	if (k < n)
		dest[o] = '\0';
	return (r);
}

/**
 **_strchr - Entry point
 *@s: input
 *@c:input
 *Return: Always 0
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

