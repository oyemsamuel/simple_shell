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
	char *path = NULL; // Stores the path to the executable
	int i, k; // Loop counters

	info->path = info->argv[0]; // Initialize path with the command name
	if (info->linecount_flag == 1)
	{
		info->line_count++; // Increment line count if linecount_flag is set
		info->linecount_flag = 0; // Reset linecount_flag
	}

	k = 0; // Initialize k to count non-delimiter characters
	for (i = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
		{
			k++; // Increment k for non-delimiter characters
		}
	}

	if (!k)
	{
		return; // If no non-delimiter characters, return
	}

	// Find the executable's path in the PATH environment variable
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path; // Set path to the found executable
		fork_cmd(info); // Execute the command
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_cmd(info); // Execute the command if it's an absolute path or built-in
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127; // Set exit status to indicate command not found
			print_error(info, "not found\n"); // Print error message
		}
	}
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
