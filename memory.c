#include "shell.h"

/**
 * bfree - Entry point
 * @ptr:input
 *
 * Return: 1 pass, 0 if fail.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

