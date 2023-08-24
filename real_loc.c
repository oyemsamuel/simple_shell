#include "shell.h"

/**
 * ffree - Frees a string of strings.
 * @pp: String of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a); /* Free a string of strings (array of pointers) */
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block of memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size)); /* If ptr is NULL, just allocate new memory */

	if (!new_size)
		return (free(ptr), NULL); /* If new_size is 0, free memory and return NULL */

	if (new_size == old_size)
		return (ptr); /* If new_size is equal to old_size, no need to reallocate */

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size]; /* Copy contents from old to new memory */

	free(ptr); /* Free the old memory */
	return (p); /* Return pointer to the new reallocated memory */
}

/**
 * _memset - Fills memory with a constant byte.
 * @s: The pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The amount of bytes to be filled.
 * Return: (s) A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s); /* Fill memory with the given byte value */
}