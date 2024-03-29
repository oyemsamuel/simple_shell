#include "shell.h"

/**
 * _myenv - Print the current environment variables.
 * @info: Pointer to the structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	/* Call function to print environment variables */
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable.
 * @info: Pointer to the structure containing potential arguments.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable if found, NULL otherwise.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p); /* Return the value of the environment variable */
		node = node->next;
	}
	return (NULL); /* Return NULL if the environment variable is not found */
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @info: Pointer to the structure containing potential arguments.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Pointer to the structure containing potential arguments.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Pointer to the structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	/* Populate the linked list with environment variables */
	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node; /* Update the environment variable linked list */
	return (0);
}
