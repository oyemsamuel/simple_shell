#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr) /* Check if the pointer and its value are valid */
	{
		free(*ptr); /* Free the memory pointed to by the pointer */
		*ptr = NULL; /* Set the pointer to NULL */
		return (1); /* Indicate that memory was freed */
	}
	return (0); /* Indicate that no memory was freed */
}