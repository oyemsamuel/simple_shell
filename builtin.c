#include "shell.h"

/**
 * _myhistory - Display the history list with line numbers.
 * @info: Pointer to the structure containing potential arguments.
 *        Used to determine whether shell is in interactive mode.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	/* Call function to print command history */
	print_list(info->history);
	return (0);
}

/**
 * _mycd - Change the current directory of the shell process
 * @info: Pointer to the structure containing potential arguments.
 *        This pointer is used to maintain the consistency of function prototypes.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *current_path, *target_dir, buffer[1024];
	int chdir_result;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	/* Handle change to home directory */
	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_result = /* TODO: What should this be? */
				chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	/* Handle change to previous directory */
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_path);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = /* TODO: What should this be? */
			chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);

	/* Handle chdir error or success */
	if (chdir_result == -1)
	{
		print_error(info, "Cannot change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Display help information
 * @info: Pointer to the structure containing potential arguments.
 *        This pointer is used to maintain the consistency of function prototypes.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* Temporary unused workaround */
	return (0);
}
