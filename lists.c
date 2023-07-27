
#include "shell.h"

list_t *add_node_to_start(list_t **head, const char *data, int index)
{
	if (!head)
		return (NULL);

	list_t *new_node = create_node(data, index);
	if (!new_node)
		return (NULL);

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

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

size_t print_list_data(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		_puts(head->data ? head->data : "(nil)");
		_puts("\n");
		head = head->next;
		size++;
	}

	return (size);
}

int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}

	list_t *prev = NULL;
	list_t *current = *head;
	unsigned int i = 0;

	while (current)
	{
		if (i == index)
		{
			prev->next = current->next;
			free(current->data);
			free(current);
			return (1);
		}
		i++;
		prev = current;
		current = current->next;
	}

	return (0);
}

void free_list(list_t **head)
{
	if (!head || !*head)
		return;

	list_t *current = *head;
	while (current)
	{
		list_t *next = current->next;
		free(current->data);
		free(current);
		current = next;
	}

	*head = NULL;
}
