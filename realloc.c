#include "shell.h"

/**
 * _memset - Entry point
 * @s: input
 * @b: input
 * @n: input
 * Return: Always 0
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int o;

	for (o = 0; o < n; o++)
		s[o] = b;
	return (s);
}

/**
 * ffree - Entry point
 * @pp: input
 */
void ffree(char **pp)
{
	char **c = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(c);
}

/**
 * _realloc - Entry point
 * @ptr: input
 * @old_size: input
 * @new_size: input
 *
 * Return: Always 0
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *y;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	y = malloc(new_size);
	if (!y)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		y[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (y);
}

