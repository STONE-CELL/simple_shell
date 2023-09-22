#include "shell.h"

/**
 * add_node -Entry point
 * @head:input
 * @str: input
 * @num: input
 *
 * Return:Always 0
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *n;

	if (!head)
		return (NULL);
	n = malloc(sizeof(list_t));
	if (!n)
		return (NULL);
	_memset((void *)n, 0, sizeof(list_t));
	n->num = num;
	if (str)
	{
		n->str = _strdup(str);
		if (!n->str)
		{
			free(n);
			return (NULL);
		}
	}
	n->next = *head;
	*head = n;
	return (n);
}

/**
 * add_node_end - Entry point
 * @head: input
 * @str:input
 * @num:input
 *
 * Return: Always 0
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *n, *d;

	if (!head)
		return (NULL);

	d = *head;
	n = malloc(sizeof(list_t));
	if (!n)
		return (NULL);
	_memset((void *)n, 0, sizeof(list_t));
	n->num = num;
	if (str)
	{
		n->str = _strdup(str);
		if (!n->str)
		{
			free(n);
			return (NULL);
		}
	}
	if (d)
	{
		while (d->next)
			d = d->next;
		d->next = n;
	}
	else
		*head = n;
	return (n);
}

/**
 * print_list_str - Entry point
 * @h: input
 *
 * Return:Always 0
 */
size_t print_list_str(const list_t *h)
{
	size_t o = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		o++;
	}
	return (o);
}

/**
 * delete_node_at_index - Entry point
 * @head: input
 * @index: input
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *n, *p;
	unsigned int o = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		n = *head;
		*head = (*head)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *head;
	while (n)
	{
		if (o == index)
		{
			p->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		o++;
		p = n;
		n = n->next;
	}
	return (0);
}

/**
 * free_list - Entry point
 * @head_ptr:input
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *d, *n, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	d = h;
	while (d)
	{
		n = d->next;
		free(d->str);
		free(d);
		d = n;
	}
	*head_ptr = NULL;
}

