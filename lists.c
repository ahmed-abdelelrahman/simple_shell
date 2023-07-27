#include "shell.h"

/**
 * add_node_to_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_start(list_t **head, const char *data, int index)
{
	if (!head)
		return (NULL);

	list_t *new_node = create_node(data, index);
	if (!new_node)
		return (NULL);

	memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;

	if (data)
	{
		new_node->data = strdup(data);
		if (!new_node->data)
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
 * add_node_to_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_end(list_t **head, const char *data, int index)
{
	if (!head)
		return (NULL);

	list_t *new_node = create_node(data, index);
	if (!new_node)
		return (NULL);

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		list_t *current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}

	return (new_node);
}

/**
 * print_list_data - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_data(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		puts(head->data ? head->data : "(nil)");
		puts("\n");
		head = head->next;
		size++;
	}

	return (size);
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
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
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
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
