#include "shell.h"

/**
 * _eputs - Prints a string to the standard error stream.
 * @str: The string to be printed.
 *
 * Return: None.
 */
void _eputs(char *str)
{
    int i;
    if (str == NULL)
    return;

    for (i = 0; str[i] != '\0'; i++)
    {
    _eputchar(str[i]);
    }
}

/**
 * _eputchar - Writes a character to the standard error stream.
 * @c: The character to be written.
 *
 * Return: On success, returns 1.
 *         On error, returns -1 and sets errno appropriately.
 */
int _eputchar(char c)
{
    static char buf[WRITE_BUF_SIZE];
    static int i ;

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
    write(2, buf, i);
    i = 0;
    }

    if (c != BUF_FLUSH)
    buf[i++] = c;

    return (1) ;
}

/**
 * _putfd - Writes a character to the specified file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 *         On error, returns -1 and sets errno appropriately.
 */
int _putfd(char c, int fd)
{
    static char buf[WRITE_BUF_SIZE];
    static int i ;

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
    write(fd, buf, i);
    i = 0;
    }

    if (c != BUF_FLUSH)
    buf[i++] = c;

    return (1) ;
}

/**
 * _putsfd - prints a string of input
 * @str: a string that will be printed
 * @fd: writing to the filedescriptor
 *
 * Return: amount of characters entered
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

