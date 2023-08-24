#include "shell.h"

/**
 * unset_alias - Remove an alias from the list.
 * @info: Pointer to the parameter struct.
 * @str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Add or update an alias in the list.
 * @info: Pointer to the parameter struct.
 * @str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str)); /* If value is empty, remove alias */

	unset_alias(info, str); /* Remove existing alias if it already exists */
	return (add_node_end(&(info->alias), str, 0) == NULL); /* Add alias to list */
}

/**
 * print_alias - Print an alias string.
 * @node: Pointer to the alias node.
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '='); /* Find the equal sign in the string */
		for (a = node->str; a <= p; a++)
			_putchar(*a); /* Print alias name */
		_putchar('\'');
		_puts(p + 1); /* Print alias value */
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimic the alias builtin command.
 * @info: Pointer to the structure containing potential arguments.
 *        Used to manage alias commands.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node); /* Print aliases */
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '='); /* Find the equal sign in the string */
		if (p)
			set_alias(info, info->argv[i]); /* Set or update alias */
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '=')); /* Print specific alias */
	}

	return (0);
}
/**
 * _myexit - Terminate the shell
 * @info: Pointer to the structure containing potential arguments.
 *        This pointer is used to maintain the consistency of function prototypes.
 * Return: Exit status: 0 if info->argv[0] is not "exit"
 */
int _myexit(info_t *info)
{
	int exit_check;

	/* Check if an exit argument is provided */
	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2); /* Return status for exit */
	}
	info->err_num = -1;
	return (-2); /* Return status for exit */
}