#include "shell.h"

/**
 * struct node_s - linked list node
 * @data: string - (malloc'ed string)
 * @index: node index used by history
 * @next: points to the next node
 *
 * Description: linked list node structure
 */
typedef struct node_s
{
    char *data;
    int index;
    struct node_s *next;
} node_t;

/**
 * add_node_to_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @data: data field of node
 * @index: node index used by history
 *
 * Return: pointer to the new head of the list
 */
node_t *add_node_to_start(node_t **head, const char *data, int index)
{
    if (!head)
        return NULL;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
        return NULL;

    memset(new_node, 0, sizeof(node_t));
    new_node->index = index;

    if (data)
    {
        new_node->data = strdup(data);
        if (!new_node->data)
        {
            free(new_node);
            return NULL;
        }
    }

    new_node->next = *head;
    *head = new_node;
    return new_node;
}

/**
 * add_node_to_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @data: data field of node
 * @index: node index used by history
 *
 * Return: pointer to the new node added at the end of the list
 */
node_t *add_node_to_end(node_t **head, const char *data, int index)
{
    if (!head)
        return NULL;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
        return NULL;

    memset(new_node, 0, sizeof(node_t));
    new_node->index = index;

    if (data)
    {
        new_node->data = strdup(data);
        if (!new_node->data)
        {
            free(new_node);
            return NULL;
        }
    }

    if (*head)
    {
        node_t *node = *head;
        while (node->next)
            node = node->next;

        node->next = new_node;
    }
    else
    {
        *head = new_node;
    }

    return new_node;
}

/**
 * print_list_data - prints only the data element of a node_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_data(const node_t *h)
{
    size_t count = 0;

    while (h)
    {
        printf("%s\n", h->data ? h->data : "(nil)");
        h = h->next;
        count++;
    }

    return count;
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(node_t **head, unsigned int index)
{
    if (!head || !*head)
        return 0;

    if (index == 0)
    {
        node_t *node = *head;
        *head = (*head)->next;
        free(node->data);
        free(node);
        return 1;
    }

    node_t *prev_node = NULL;
    node_t *node = *head;
    unsigned int i = 0;

    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->data);
            free(node);
            return 1;
        }
        i++;
        prev_node = node;
        node = node->next;
    }

    return 0;
}

/**
 * free_list - frees all nodes of a node_t linked list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(node_t **head_ptr)
{
    node_t *node = *head_ptr;
    node_t *next_node;

    while (node)
    {
        next_node = node->next;
        free(node->data);
        free(node);
        node = next_node;
    }

    *head_ptr = NULL;
}
