#include "shell.h"

/**
 * _memset - a constant byte is stored in memory
 * @str: the memory area's pointing device
 * @ch: the byte to use in filling *str
 * @n: the number of bytes that must be filled
 *
 * Return: an indicator of the memory location str
 */
char *_memset(char *str, char ch, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = ch;
	return (str);
}

/**
 * ffree - releases a group of strings
 * @str_arr: multi-string ensemble
 */
void ffree(char **str_arr)
{
	char **arr = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(arr);
}

/**
 * _realloc - blocks of memory are reallocated
 * @ptr: identifier of a previously malloc'd block
 * @old_size: Byte size of the preceding block
 * @new_size: new block's byte size
 *
 * Return: pointer to either a new or old block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

