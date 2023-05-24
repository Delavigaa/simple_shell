#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to copy to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: The pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *str = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
    dest[i] = src[i];
    i++;
    }
    if (i < n)
    {
    j = i;
    while (j < n)
    {
    dest[j] = '\0';
    j++;
    }
    }
    return (str);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: The pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *str = dest;

    i = 0;
    j = 0;
    while (dest[i] != '\0')
    {
    i++;
    }
    while (src[j] != '\0' && j < n)
    {
    dest[i] = src[j];
    i++;
    j++;
    }
    if (j < n)
    {
    dest[i] = '\0';
}
    return (str);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
    char *ptr = s;

    do {
    if (*ptr == c)
    {
    return (ptr);
    }
    ptr++;
    } while (*ptr != '\0');

    return (NULL);
}

