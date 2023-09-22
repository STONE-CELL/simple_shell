#include "shell.h"

/**
 * _myhistory - Entry point
 * @info: input
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Entry point
 * @info: input
 * @str: input
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *o, a;
	int t;

	o = _strchr(str, '=');
	if (!o)
		return (1);
	a = *o;
	*o = 0;
	t = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*o = a;
	return (t);
}

/**
 * set_alias - Entry point
 * @info: input
 * @str: input
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *o;

	o = _strchr(str, '=');
	if (!o)
		return (1);
	if (!*++o)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Entry point
 * @node: input
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *o = NULL, *c = NULL;

	if (node)
	{
		o = _strchr(node->str, '=');
		for (c = node->str; c <= o; c++)
		_putchar(*c);
		_putchar('\'');
		_puts(o + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Entry point
 * @info:input
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int y = 0;
	char *o = NULL;
	list_t *n = NULL;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			print_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (y = 1; info->argv[y]; y++)
	{
		o = _strchr(info->argv[y], '=');
		if (o)
			set_alias(info, info->argv[y]);
		else
			print_alias(node_starts_with(info->alias, info->argv[y], '='));
	}

	return (0);
}

