#include "shell.h"

/**
 * set_info - Initializes an info_t struct with provided arguments.
 * @info: Pointer to the info_t struct to be initialized.
 * @av: Argument vector (array of strings).
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees the memory associated with an info_t struct's fields.
 * @info: Pointer to the info_t struct to be freed.
 * @all: Flag indicating whether to free all fields or not.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv); /* Free the argv array */
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg); /* Free the command argument string */
		if (info->env)
			free_list(&(info->env)); /* Free the environment linked list */
		if (info->history)
			free_list(&(info->history)); /* Free the history linked list */
		if (info->alias)
			free_list(&(info->alias)); /* Free the alias linked list */
		ffree(info->environ); /* Free the environment strings array */
		info->environ = NULL;
		bfree((void **)info->cmd_buf); /* Free the command buffer */
		if (info->readfd > 2)
			close(info->readfd); /* Close the read file descriptor */
		_putchar(BUF_FLUSH); /* Flush the output buffer */
	}
}

/**
 * clear_info - Initializes an info_t struct by setting its fields to NULL.
 * @info: Pointer to the info_t struct to be cleared.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}