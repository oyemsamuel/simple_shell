#include "shell.h"

/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @str: str field of node.
 * @num: node index used by history.
 *
 * Return: Pointer to the newly added node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t)); /* Allocate memory for the new node */
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t)); /* Initialize the new node */
	new_node->num = num; /* Set the node index */
	if (str)
	{
		new_node->str = _strdup(str); /* Duplicate and set the string */
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node; /* Append the new node to the end of the list */
	}
	else
		*head = new_node; /* Update the head pointer if the list was empty */
	return (new_node);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)"); /* Print the string or "(nil)" */
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i); /* Return the size of the list */
}

/**
 * delete_node_at_index - Deletes a node at a given index.
 * @head: Address of pointer to first node.
 * @index: Index of node to delete.
 *
 * Return: 1 on success, 0 on failure.
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
		*head = (*head)->next; /* Update the head pointer */
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next; /* Update the previous node's next pointer */
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
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to head node.
 *
 * Return: void.
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
	*head_ptr = NULL; /* Set the head pointer to NULL to indicate an empty list */
}

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}