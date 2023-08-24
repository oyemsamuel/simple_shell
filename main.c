#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 * 
 * Return: 0 on success, 1 on error.
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT }; /* Initialize the info_t struct */
	int fd = 2; /* File descriptor for error output */

	/* Inline assembly code to manipulate the file descriptor */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);/* Open a file for reading */
		if (fd == -1)
		{
			if (errno == EACCES) /* Permission denied */
				exit(126); /* Exit with error code 126 */
			if (errno == ENOENT) /* No such file or directory */
			{
				_eputs(av[0]); /* Print program name */
				_eputs(": 0: Can't open ");
				_eputs(av[1]); /* Print file name */
				_eputchar('\n');
				_eputchar(BUF_FLUSH); /* Flush error buffer */
				exit(127); /* Exit with error code 127 */
			}
			return (EXIT_FAILURE); /* Return EXIT_FAILURE if open fails */
		}
		info->readfd = fd; /* Set readfd in the info struct */
	}
	populate_env_list(info); /* Populate the environment list in the info struct */
	read_history(info); /* Read command history from a file */
	hsh(info, av); /* Read command history from a file */
	return (EXIT_SUCCESS); /* Return EXIT_SUCCESS on successful execution */
}
