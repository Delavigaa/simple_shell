#include "shell.h"

/**
 * _strcpy - copied from source to destination is a string.
 * @new_dest: the string's final location.
 * @new_src: the original text.
 *
 * Return: a reference to the final string.
 */
char *_strcpy(char *new_dest, char *new_src)
{
	int new_i = 0;

	if (new_dest == new_src || new_src == 0)
		return (new_dest);
	while (new_src[new_i])
	{
		new_dest[new_i] = new_src[new_i];
		new_i++;
	}
	new_dest[new_i] = 0;
	return (new_dest);
}

/**
 * _strdup - copies a string exactly.
 * @new_str: the string you should copy.
 *
 * Return: a reference to the repeated string.
 */
char *_strdup(const char *new_str)
{
	int new_length = 0;
	char *new_ret;

	if (new_str == NULL)
		return (NULL);
	while (*new_str++)
		new_length++;
	new_ret = malloc(sizeof(char) * (new_length + 1));
	if (!new_ret)
		return (NULL);
	for (new_length++; new_length--;)
		new_ret[new_length] = *--new_str;
	return (new_ret);
}

/**
 * _puts - an input string is printed.
 * @new_str: the string to be shown.
 *
 * Return:  Nothing
 */
void _puts(char *new_str)
{
	int new_i = 0;

	if (!new_str)
		return;
	while (new_str[new_i] != '\0')
	{
		_putchar(new_str[new_i]);
		new_i++;
	}
}

/**
 * _putchar - stdout is updated with the letter C.
 * @new_c: The text to be printed.
 *
 * Return: Regarding achievement 1.
 *      Errno is set correctly and -1 is given in the event of an         error.
 */
int _putchar(char new_c)
{
	static int new_i;
	static char new_buf[WRITE_BUF_SIZE];

	if (new_c == BUF_FLUSH || new_i >= WRITE_BUF_SIZE)
	{
		write(1, new_buf, new_i);
		new_i = 0;
	}
	if (new_c != BUF_FLUSH)
		new_buf[new_i++] = new_c;
	return (1);
}

