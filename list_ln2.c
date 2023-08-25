#include "shell.h"

/**
 * list_to_strings - Returns an array of strings of the list->str.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1)); /* Allocate memory to arr strings */
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1); /* Allocate memory for each str */
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]); /* Free previously allocated strings */
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str); /* Copy the str into the allocated memory */
		strs[i] = str;
	}
	strs[i] = NULL; /* Set the last element of the array to NULL */
	return (strs);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0)); /* Print the node number */
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)"); /* Print the string or "(nil)" */
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i); /* Return the size of the list */
}

/**
 * node_starts_with - Returns a node whose string starts with prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 *
 * Return: Matching node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * add_node - Adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: str field of node.
 * @num: node index used by history.
 *
 * Return: Pointer to the newly added node.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t)); /* Allocate memory for the new node */
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t)); /* Initialize the new node */
	new_head->num = num; /* Set the node index */
	if (str)
	{
		new_head->str = _strdup(str); /* Duplicate and set the string */
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head; /* Set the next pointer of the new node */
	*head = new_head; /* Update the head pointer */
	return (new_head);
}
