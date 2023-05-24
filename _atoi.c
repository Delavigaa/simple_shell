#include "shell.h"

/**
 * interactive - Returns true if the shell is running in interactive mode
 * @info: Pointer to the Info_t struct
 *
 * Return: 1 if running in interactive mode, 0 otherwise
 */
int interactive(Info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1);
	else
		return (0);
}

/**
 * is_delim - Checks if a character is a delimiter
 * @c: The character to check
 * @delim: The delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}

	return (0);
}

/**
 * _isalpha - Checks if a character is alphabetic
 * @c: The character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer
 * @s: The string to be converted
 *
 * Return: The converted integer if successful, 0 if the string has no numbers
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	output = (sign == -1) ? -result : result;
	return (output);
}

