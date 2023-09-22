#include "shell.h"

/**
 * get_history_file - Entry point
 * @info: input
 *
 * Return: Always 0
 */

char *get_history_file(info_t *info)
{
	char *b, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}

/**
 * write_history - Entry point
 * @info:input
 *
 * Return: 1 if pass, -1 if fail
 */
int write_history(info_t *info)
{
	ssize_t h;
	char *f = get_history_file(info);
	list_t *node = NULL;

	if (!f)
		return (-1);

	h = open(f, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f);
	if (h == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, h);
		_putfd('\n', h);
	}
	_putfd(BUF_FLUSH, h);
	close(h);
	return (1);
}

/**
 * read_history - Entry point
 * @info: input
 *
 * Return: histcount on success, 0 if fail
 */
int read_history(info_t *info)
{
	int o, l = 0, c = 0;
	ssize_t h, r, z = 0;
	struct stat st;
	char *b = NULL, *f = get_history_file(info);

	if (!f)
		return (0);

	h = open(f, O_RDONLY);
	free(f);
	if (h == -1)
		return (0);
	if (!fstat(h, &st))
		z = st.st_size;
	if (z < 2)
		return (0);
	b = malloc(sizeof(char) * (z + 1));
	if (!b)
		return (0);
	r = read(h, b, z);
	b[z] = 0;
	if (r <= 0)
		return (free(b), 0);
	close(h);
	for (o = 0; o < z; o++)
		if (b[o] == '\n')
		{
			b[o] = 0;
			build_history_list(info, b + l, c++);
			l = o + 1;
		}
	if (l != o)
		build_history_list(info, b + l, c++);
	free(b);
	info->histcount = c;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Entry point
 * @info: input
 * @buf: input
 * @linecount: input
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Entry point
 * @info: input
 *
 * Return: Always 0
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int o = 0;

	while (node)
	{
		node->num = o++;
		node = node->next;
	}
	return (info->histcount = o);
	
}

