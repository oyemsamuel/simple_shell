#include "shell.h"

/**
 * _strncpy - Copies a string with a specified length.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	/* Copy characters from src to dest up to n characters */
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	/* Fill remaining characters in dest with '\0' */
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings up to a specified length.
 * @dest: The destination string.
 * @src: The source string to be appended.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: A pointer to the destination string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	/* Find the end of the destination string */
	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	/* Append characters from src to dest up to n characters */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	/* Ensure the destination string is null-terminated */
	if (j < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: The string to be searched.
 * @c: The character to search for.
 *
 * Return: A pointer to the first occurrence of the character in the string.
 * If the character is not found, returns NULL.
 */
char *_strchr(char *s, char c)
{
	/* Search for the character c in the string s */
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL); /* Character not found */
}
