#include "shell.h"

/**
 * get_environ - Entry point
 * @info: input
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Entry point
 * @info: input
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t o = 0;
	char *y;

	if (!node || !var)
		return (0);

	while (node)
	{
		y = starts_with(node->str, var);
		if (y && *y == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), o);
			o = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		o++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Entry point
 * @info:input
 * @var:input
 * @value: input
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *b = NULL;
	list_t *node;
	char *y;

	if (!var || !value)
		return (0);

	b = malloc(_strlen(var) + _strlen(value) + 2);
	if (!b)
		return (1);
	_strcpy(b, var);
	_strcat(b, "=");
	_strcat(b, value);
	node = info->env;
	while (node)
	{
		y = starts_with(node->str, var);
		if (y && *y == '=')
		{
			free(node->str);
			node->str = b;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), b, 0);
	free(b);
	info->env_changed = 1;
	return (0);
}

