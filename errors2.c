#include "shell.h"

/**
 * print_error - Prints an error message to the standard error (stderr).
 * @info: The parameter and return info struct.
 * @estr: String containing specified error type.
 *
 * Return: Nothing.
 */
void print_error(info_t *info, char *estr)
{
	/* Print error details: filename, line number, command name, and error type */
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	/* Determine whether to use standard output or standard error */
	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	/* Handle negative numbers */
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	
	/* Print each digit of the number */
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a number to a string representation.
 * @num: The number to be converted.
 * @base: The base for conversion (e.g., 10 for decimal).
 * @flags: Flags indicating conversion options.
 *
 * Return: The string representation of the number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	/* Handle negative numbers if applicable */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	/* Determine array of characters for the given base */
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	/* Convert the number to a string representation */
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Nothing.
 */
void remove_comments(char *buf)
{
	int i;

	/* Find the first instance of '#' and replace with '\0' */
	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
/**
 * _erratoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number if successful, -1 on error.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	/* Skip '+' sign if present */
	if (*s == '+')
		s++;

	/* Convert string to integer */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			
			/* Check for integer overflow */
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1); /* Invalid character encountered */
	}

	return (result);
}