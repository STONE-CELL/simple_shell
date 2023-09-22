#include "shell.h"

/**
 * input_buf - Entry point
 * @info: input
 * @buf: input
 * @len: input
 *
 * Return: Always 0
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t t = 0;
	size_t p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(buf, &p, stdin);
#else
		t = _getline(info, buf, &p);
#endif
		if (t > 0)
		{
			if ((*buf)[t - 1] == '\n')
			{
				(*buf)[t - 1] = '\0'; /* remove trailing newline */
				t--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = t;
				info->cmd_buf = buf;
			}
		}
	}
	return (t);
}

/**
 * get_input - Entry point
 * @info: input
 *
 * Return: Always 0
 */
ssize_t get_input(info_t *info)
{
	static char *b; /* the ';' command chain buffer */
	static size_t o, k, l;
	ssize_t t = 0;
	char **f = &(info->arg), *y;

	_putchar(BUF_FLUSH);
	t = input_buf(info, &b, &l);
	if (t == -1) /* EOF */
		return (-1);
	if (l) /* we have commands left in the chain buffer */
	{
		k = o; /* init new iterator to current buf position */
		y = b + o; /* get pointer for return */

		check_chain(info, b, &k, o, l);
		while (k < l) /* iterate to semicolon or end */
		{
			if (is_chain(info, b, &k))
				break;
			k++;
		}

		o = k + 1; /* increment past nulled ';'' */
		if (o >= l) /* reached end of buffer? */
		{
			o = l = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*f = y; /* pass back pointer to current command position */
		return (_strlen(y)); /* return length of current command */
	}

	*f = b; /* else not a chain, pass back buffer from _getline() */
	return (t); /* return length of buffer from _getline() */
}

/**
 * read_buf - Entry point
 * @info: input
 * @buf:input
 * @i:input
 *
 * Return: Always 0
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(info->readfd, buf, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 * _getline - Entry point
 * @info: input
 * @ptr: input
 * @length:input
 *
 * Return:Always 0
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t o, l;
	size_t u;
	ssize_t t = 0, w = 0;
	char *y = NULL, *n = NULL, *a;

	y = *ptr;
	if (y && length)
		w = *length;
	if (o == l)
		o = l = 0;

	t = read_buf(info, buf, &l);
	if (t == -1 || (t == 0 && l == 0))
		return (-1);

	a = _strchr(buf + o, '\n');
	u = a ? 1 + (unsigned int)(a - buf) : l;
	n = _realloc(y, w, w ? w + u : u + 1);
	if (!n) 
		return (y ? free(y), -1 : -1);

	if (w)
		_strncat(n, buf + o, u - o);
	else
		_strncpy(n, buf + o, u - o + 1);

	w += u - o;
	o = u;
	y = n;

	if (length)
		*length = w;
	*ptr = y;
	return (w);
}

/**
 * sigintHandler - Entry point
 * @sig_num: input
 *
 * Return: Always 0
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

