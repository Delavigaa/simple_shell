#include "shell.h"

/**
 * _strlen - The length of a string is calculated.
 * @s: the string whose length to compute.
 *
 * Return: long the string is.
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (*s++)
		len++;
	return (len);
}

/**
 * _strcmp - compares the lexical structures of two strings.
 * @s1: 1_string.
 * @s2: 2_string.
 *
 * Return: Zero if s1 == (*s1 < *s2 ? -1 : 1), and negative otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - makes sure the haystack is at the top of the needle.
 * @haystack: the string to look for.
 * @needle: he needed substring.
 *
 * Return: the address of the following haystack character or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - joins two threads together.
 * @dest: is the final buffer.
 * @src: the last buffer, is.
 *
 * Return: identifier for the last buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}

