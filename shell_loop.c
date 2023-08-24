#include "shell.h"

/**
 * find_builtin - Finds a builtin command.
 * @info: The parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int built_in_ret = -1;
	int i;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret); /* Return the result of the builtin command execution */
}

/**
 * find_cmd - Finds a command in PATH.
 * @info: The parameter & return info struct.
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i;

    for (i = 0; info->env[i]; i++)
    {
        if (_strncmp(info->env[i], "PATH=", 5) == 0)
        {
            path = _strdup(info->env[i] + 5);
            break;
        }
    }

    if (path == NULL)
        return; // Could not find PATH in the environment

    char *token, *cmd_path;
    char *saveptr = NULL;

    token = _strtok_r(path, ":", &saveptr);
    while (token != NULL)
    {
        cmd_path = _strcat(_strcat(token, "/"), info->argv[0]);
        if (access(cmd_path, F_OK) == 0)
        {
            info->path = cmd_path;
            free(path);
            return; // Found the executable
        }
        free(cmd_path);
        token = _strtok_r(NULL, ":", &saveptr);
    }

    free(path);
    _eputs("Command not found\n");
    info->path = NULL;
}

/**
 * fork_cmd - Forks an exec thread to run a command.
 * @info: The parameter & return info struct.
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork(); /* Fork a child process */
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		/* Child process */
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* ... */
	}
	else
	{
		/* Parent process */
		wait(&(info->status)); /* Wait for the child process to finish */
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * hsh - Main shell loop.
 * @info: The parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info); /* Read user input */
		if (r != -1)
		{
			set_info(info, av); /* Prepare command info */
			builtin_ret = find_builtin(info); /* Check if it's a built-in command */
			if (builtin_ret == -1)
				find_cmd(info); /* If not built-in, find and execute the command */
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0); /* Free temporary info fields */
	}
	write_history(info); /* Save history */
	free_info(info, 1); /* Free all info fields */
	if (!interactive(info) && info->status)
		exit(info->status); /* Exit with the command's exit status */
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num); /* Exit with error number if needed */
	}
	return (builtin_ret);
}
