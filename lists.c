#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_node = malloc(sizeof(list_t));
	// function adds a new node to the start of the linked list.
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		list_t *node = *head;
		while (node->next)
			node = node->next;
		node->next = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	list_t *prev_node = NULL;
	list_t *current_node = *head;
	unsigned int i = 0;

	while (current_node)
	{
		if (i == index)
		{
			prev_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		i++;
		prev_node = current_node;
		current_node = current_node->next;
	}

	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	if (!head_ptr || !*head_ptr)
		return;

	list_t *node = *head_ptr;
	while (node)
	{
		list_t *next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
