#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The converted integer if successful, or -1 on error.
 */
int _erratoi(char *str)
{
    int index = 0;
    unsigned long int result = 0;

    if (*str == '+')
    str++;

    for (index = 0; str[index] != '\0'; index++)
    {
    if (str[index] >= '0' && str[index] <= '9')
    {
    result = result * 10 + (str[index] - '0');
    if (result > INT_MAX)
    return (-1) ;
    }
    else
    return (-1) ;
    }

    return (result) ;
}

/**
 * print_error - Prints an error message.
 * @info: Pointer to the parameter and return info struct.
 * @error_string: String containing the specified error type.
 */
void print_error(Info_t *info, char *error_string)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(error_string);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @number: The number to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_d(int number, int fd)
{
    int (*putchar_func)(char) = fd == STDERR_FILENO ? _eputchar : _putchar;
    int i, count = 0;
    unsigned int abs_value, current;

    if (number < 0)
    {
    abs_value = (unsigned int)(-number);
    putchar_func('-');
    count++;
    }
    else
    {
    abs_value = (unsigned int)number;
    }

    current = abs_value;

    for (i = 1000000000; i > 1; i /= 10)
    {
    if (abs_value / i)
    {
    putchar_func('0' + current / i);
    count++;
    }
    current %= i;
    }

    putchar_func('0' + current);
    count++;

    return (count) ;
}

/**
 * convert_number - Converts a number to a string representation.
 * @num: The number to be converted.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */
char *convert_number(long int num, int base, int flags)
{
    static char buffer[50];
    char *ptr;
    unsigned long n = num;
    char sign = 0;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
    n = -num;
    sign = '-';
    }

    ptr = &buffer[49];
    *ptr = '\0';

    do {
    *--ptr = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef"[n % base] : "0123456789ABCDEF"[n % base];
    n /= base;
    } while (n != 0);

    if (sign)
    *--ptr = sign;

    return (ptr) ;
}

/**
 * remove_comments - Removes comments from a string.
 * @buf: The string to modify.
 *
 * Return: None.
 */
void remove_comments(char *buf)
{
    int i;
    for (i = 0; buf[i] != '\0'; i++)
    {
    if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
    {
    buf[i] = '\0';
    break;
    }
    }
}

