#include "shell.h"

/**
 * is_cmd - Entry point
 * @info: input
 * @path: input
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Entry point
 * @pathstr: input
 * @start: input
 * @stop: input
 *
 * Return: Always 0
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int o = 0, u = 0;

	for (u = 0, o = start; o < stop; o++)
		if (pathstr[o] != ':')
			buf[u++] = pathstr[o];
	buf[u] = 0;
	return (buf);
}

/**
 * find_path - Entry point
 * @info: input
 * @pathstr: input
 * @cmd: input
 *
 * Return: Always 0
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int o = 0, c = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[o] || pathstr[o] == ':')
		{
			p = dup_chars(pathstr, c, o);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[o])
				break;
			c = o;
		}
		o++;
	}
	return (NULL);
}

