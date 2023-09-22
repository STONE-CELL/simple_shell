#include "shell.h"

/**
 * _myenv - Entry point
 * @info:input
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Entry point
 * @info: input
 * @name: input
 *
 * Return: Always 0
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *o;

	while (node)
	{
		o = starts_with(node->str, name);
		if (o && *o)
			return (o);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Entry point
 * @info: input
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Entry point
 * @info: input
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int o;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (o = 1; o <= info->argc; o++)
		_unsetenv(info, info->argv[o]);

	return (0);
}

/**
 * populate_env_list - Entry point
 * @info:input
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *n = NULL;
	size_t o;

	for (o = 0; environ[o]; o++)
		add_node_end(&n, environ[o], 0);
	info->env = n;
	return (0);
}

