#include "shell.h"

/**
 * **strtow - Entry point
 * @str: input
 * @d: input
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int o, h, u, n, p = 0;
	char **w;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (o = 0; str[o] != '\0'; o++)
		if (!is_delim(str[o], d) && (is_delim(str[o + 1], d) || !str[o + 1]))
			p++;

	if (p == 0)
		return (NULL);
	w = malloc((1 + p) * sizeof(char *));
	if (!w)
		return (NULL);
	for (o = 0, h = 0; h < p; h++)
	{
		while (is_delim(str[o], d))
			o++;
		u = 0;
		while (!is_delim(str[o + u], d) && str[o + u])
			u++;
		w[h] = malloc((u + 1) * sizeof(char));
		if (!w[h])
		{
			for (u = 0; u < h; u++)
				free(w[u]);
			free(w);
			return (NULL);
		}
		for (n = 0; n < u; n++)
			w[h][n] = str[o++];
		w[h][n] = 0;
	}
	w[h] = NULL;
	return (w);
}

/**
 * **strtow2 - Entry point
 * @str: input
 * @d: input
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int o, h, u, n, p = 0;
	char **w;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (o = 0; str[o] != '\0'; o++)
		if ((str[o] != d && str[o + 1] == d) ||
				    (str[o] != d && !str[o + 1]) || str[o + 1] == d)
			p++;
	if (p == 0)
		return (NULL);
	w = malloc((1 + p) * sizeof(char *));
	if (!w)
		return (NULL);
	for (o = 0, h = 0; h < p; h++)
	{
		while (str[o] == d && str[o] != d)
			o++;
		u = 0;
		while (str[o + u] != d && str[o + u] && str[o + u] != d)
			u++;
		w[h] = malloc((u + 1) * sizeof(char));
		if (!w[h])
		{
			for (u = 0; u < h; u++)
				free(w[u]);
			free(w);
			return (NULL);
		}
		for (n = 0; n < u; n++)
			w[h][n] = str[o++];
		w[h][n] = 0;
	}
	w[h] = NULL;
	return (w);
}

