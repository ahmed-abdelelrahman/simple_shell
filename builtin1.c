#include "shell.h"

/**
 * robir_myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int robir_myhistory(inforobir_t *inforobir)
{
	print_list(inforobir->history);
	return (0);
}

/**
 * robir_unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int robir_unset_alias(inforobir_t *inforobir, char *robir_str)
{
	char *r, k;
	int retory;

	r = _strchr(robir_str, '=');
	if (!r)
		return (1);
	k = *r;
	*r = 0;
	retory = delete_node_at_index(&(inforobir->alias),
		get_node_index(inforobir->alias, node_starts_with(inforobir->alias, robir_str, -1)));
	*r = k;
	return (retory);
}

/**
 * robir_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int robir_set_alias(inforobir_t *inforobir, char *robir_str)
{
	char *r;

	r = _strchr(robir_str, '=');
	if (!r)
		return (1);
	if (!*++r)
		return (robir_unset_alias(inforobir, robir_str));

	robir_unset_alias(inforobir, robir_str);
	return (add_node_end(&(inforobir->alias), robir_str, 0) == NULL);
}

/**
 * robir_print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int robir_print_alias(list_t *node)
{
	char *r = NULL, *o = NULL;

	if (node)
	{
		r = _strchr(node->robir_str, '=');
		for (o = node->robir_str; o <= r; o++)
			_putchar(*o);
		_putchar('\'');
		_puts(r + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * robir_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.t
 *  Return: Always 0
 */
int robir_myalias(inforobir_t *inforobir)
{
	int y = 0;
	char *t = NULL;
	list_t *node = NULL;

	if (inforobir->argc == 1)
	{
		node = inforobir->robir_alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (y = 1; info->argv[y]; y++)
	{
		t = _strchr(inforobir->argv[y], '=');
		if (t)
			set_alias(inforobir, inforobir->argv[y]);
		else
			print_alias(node_starts_with(inforobir->robir_alias, inforobir->argv[y], '='));
	}

	return (0);
}
