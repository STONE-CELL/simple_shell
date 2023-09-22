#include "shell.h"

/**
 * _strlen - Entry point
 * @s: input
 *
 * Return: Always 0
 */
int _strlen(char *s)
{
	int o = 0;

	if (!s)
		return (0);

	while (*s++)
		o++;
	return (o);
}

/**
 * _strcmp - Entry point
 * @s1: input
 * @s2: input
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Entry point
 * @haystack: input
 * @needle: input
 *
 * Return: Always 0
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Entry point
 * @dest: input
 * @src: input
 *
 * Return: Always 0
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}

