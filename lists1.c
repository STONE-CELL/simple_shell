#include "shell.h"

/**
 * list_len - Entry point
 * @h: input
 *
 * Return: Always 0
 */
size_t list_len(const list_t *h)
{
	size_t o = 0;

	while (h)
	{
		h = h->next;
		o++;
	}
	return (o);
}

/**
 * list_to_strings - Entry point
 * @head: input
 *
 * Return: Always 0
 */
char **list_to_strings(list_t *head)
{
	list_t *n = head;
	size_t o = list_len(head), k;
	char **s;
	char *str;

	if (!head || !o)
		return (NULL);
	s = malloc(sizeof(char *) * (o + 1));
	if (!s)
		return (NULL);
	for (o = 0; n; n = n->next, o++)
	{
		str = malloc(_strlen(n->str) + 1);
		if (!str)
		{
			for (k = 0; k < o; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		str = _strcpy(str, n->str);
		s[o] = str;
	}
	s[o] = NULL;
	return (s);
}


/**
 * print_list - Entry point
 * @h: input
 *
 * Return:Always 0
 */
size_t print_list(const list_t *h)
{
	size_t o = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		o++;
	}
	return (o);
}

/**
 * node_starts_with - Entry point
 * @node: input
 * @prefix: input
 * @c: input
 *
 * Return: Always 0
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *y = NULL;

	while (node)
	{
		y = starts_with(node->str, prefix);
		if (y && ((c == -1) || (*y == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Entry point
 * @head: input
 * @node: input
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t o = 0;

	while (head)
	{
		if (head == node)
			return (o);
		head = head->next;
		o++;
	}
	return (-1);
}

