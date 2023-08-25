#include "shell.h"

/**
 * _eputchar - Writes the character c to the standard error (stderr).
 * @c: The character to print.
 *
 * Return: On success 1. On error, -1 is returned, and errno is set appr..
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	/* If buffer is full or the character is BUF_FLUSH, flush the buffer */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i); /* Write the buffer to stderr */
		i = 0;
	}

	/* If character is not BUF_FLUSH, add it to the buffer */
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1. On error, -1 is returned, and errno is set appr.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	/* If buffer is full or the character is BUF_FLUSH, flush the buffer */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i); /* Write the buffer to the given file descriptor */
		i = 0;
	}

	/* If character is not BUF_FLUSH, add it to the buffer */
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	/* Print each character of the string to the given file descriptor */
	while (*str)
	{
		i += _putfd(*str++, fd);
	}

	return (i);
}
/**
 * _eputs - Prints an input string to the standard error (stderr).
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	/* Print each character of the string to stderr */
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
