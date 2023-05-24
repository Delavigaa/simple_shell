#include "shell.h"

/**
 * bfree - NULLizes the address and releases a pointer
 * @new_ptr: the pointer's address to free
 *
 * Return: If released, 1; otherwise, 0
 */
int bfree(void **new_ptr)
{
	if (new_ptr && *new_ptr)
	{
		free(*new_ptr);
		*new_ptr = NULL;
		return (1);
	}
	return (0);
}

