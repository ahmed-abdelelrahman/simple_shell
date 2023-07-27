#include "shell.h"

/**
 * add_node_to_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @data: data to be stored in the new node
 * @index: node index used by history
 *
 * Return: pointer to the new node
 */
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

// Add a blank line here

/**
 * add_node_to_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @data: data to be stored in the new node
 * @index: node index used by history
 *
 * Return: pointer to the new node
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

// Add a blank line here

/**
 * print_list_data - prints the data of each node in the list
 * @head: pointer to first node
 *
 * Return: size of list
 */
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

// Add a blank line here

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

// Add a blank line here

/**
 * free_list - frees all nodes of a list
 * @head: address of pointer to head node
 *
 * Return: void
 */
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
