#include "shell.h"

/**
 * add_history_node - adds a node to the start of the history list
 * @history_head: address of pointer to head node of history list
 * @command: command to be added to the history list
 * @index: index of the command in the history list
 *
 * Return: pointer to the new node
 */
history_t *add_history_node(history_t **history_head, const char *command, int index)
{
    history_t *new_node;

    if (!history_head)
        return (NULL);

    new_node = malloc(sizeof(history_t));
    if (!new_node)
        return (NULL);

    _memset((void *)new_node, 0, sizeof(history_t));
    new_node->index = index;

    if (command)
    {
        new_node->command = _strdup(command);
        if (!new_node->command)
        {
            free(new_node);
            return (NULL);
        }
    }

    new_node->next = *history_head;
    *history_head = new_node;
    return (new_node);
}

/**
 * add_node_to_end - adds a node to the end of the linked list
 * @head: address of pointer to head node
 * @data: data field of the new node
 * @index: index of the node
 *
 * Return: pointer to the new node
 */
node_t *add_node_to_end(node_t **head, const char *data, int index)
{
	node_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(node_t));
	new_node->index = index;

	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_data - prints only the data element of a linked list
 * @head: pointer to the head node
 *
 * Return: size of the list
 */
size_t print_list_data(const node_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->data ? head->data : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes a node at the given index
 * @head: address of pointer to head node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	node_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
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
 * free_linked_list - frees all nodes of a linked list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_linked_list(node_t **head_ptr)
{
	node_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
