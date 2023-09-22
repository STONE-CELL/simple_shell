#include "shell.h"

/**
 * is_chain - Entry point
 * @info: input
 * @buf: input
 * @p: input
 *
 * Return: 1 if pass, 0 if fails
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') 
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * check_chain - Entry point
 * @info: input
 * @buf: input
 * @p: input
 * @i: input
 * @len: input
 *
 * Return: Always 0
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replace_alias - Entry point
 * @info:input
 *
 * Return: 1 if pass, 0 if fails
 */
int replace_alias(info_t *info)
{
	int o;
	list_t *node;
	char *y;

	for (o = 0; o < 10; o++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		y = _strchr(node->str, '=');
		if (!y)
			return (0);
		y = _strdup(y + 1);
		if (!y)
			return (0);
		info->argv[0] = y;
	}
	return (1);
}

/**
 * replace_vars - Entry point
 * @info: input
 *
 * Return: 1 if pass, 0 if fail
 */
int replace_vars(info_t *info)
{
	int o = 0;
	list_t *node;

	for (o = 0; info->argv[o]; o++)
	{
		if (info->argv[o][0] != '$' || !info->argv[o][1])
			continue;

		if (!_strcmp(info->argv[o], "$?"))
		{
			replace_string(&(info->argv[o]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[o], "$$"))
		{
			replace_string(&(info->argv[o]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[o][1], '=');
		if (node)
		{
			replace_string(&(info->argv[o]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[o], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Entry point
 * @old: input
 * @new: input
 *
 * Return: 1 if pass, 0 if fail
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

