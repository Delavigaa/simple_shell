#include "shell.h"

/**
 * **strtow - word-by-word separates a string, ignoring repeat delimiters.
 * @new_str: the text entered.
 * @new_d: the separator character set.
 * Return: a pointer to a collection of strings, or NULL in the event of failure.
 */
char **strtow(char *new_str, char *new_d)
{
	int new_i, new_j, new_k, new_m, new_numwords = 0;
	char **new_s;

	if (new_str == NULL || new_str[0] == 0)
		return (NULL);
	if (!new_d)
		new_d = " ";
	for (new_i = 0; new_str[new_i] != '\0'; new_i++)
		if (!is_delim(new_str[new_i], new_d) && (is_delim(new_str[new_i + 1], new_d) || !new_str[new_i + 1]))
			new_numwords++;

	if (new_numwords == 0)
		return (NULL);
	new_s = malloc((1 + new_numwords) * sizeof(char *));
	if (!new_s)
		return (NULL);
	for (new_i = 0, new_j = 0; new_j < new_numwords; new_j++)
	{
		while (is_delim(new_str[new_i], new_d))
			new_i++;
		new_k = 0;
		while (!is_delim(new_str[new_i + new_k], new_d) && new_str[new_i + new_k])
			new_k++;
		new_s[new_j] = malloc((new_k + 1) * sizeof(char));
		if (!new_s[new_j])
		{
			for (new_k = 0; new_k < new_j; new_k++)
				free(new_s[new_k]);
			free(new_s);
			return (NULL);
		}
		for (new_m = 0; new_m < new_k; new_m++)
			new_s[new_j][new_m] = new_str[new_i++];
		new_s[new_j][new_m] = 0;
	}
	new_s[new_j] = NULL;
	return (new_s);
}

/**
 * **strtow2 - uses a single delimiter to divide a text into words.
 * @new_str: the text entered.
 * @new_d: the boundary.
 * Return: a pointer to a collection of strings, or NULL in the event of failure.
 */
char **strtow2(char *new_str, char new_d)
{
	int new_i, new_j, new_k, new_m, new_numwords = 0;
	char **new_s;

	if (new_str == NULL || new_str[0] == 0)
		return (NULL);
	for (new_i = 0; new_str[new_i] != '\0'; new_i++)
		if ((new_str[new_i] != new_d && new_str[new_i + 1] == new_d) ||
				    (new_str[new_i] != new_d && !new_str[new_i + 1]) || new_str[new_i + 1] == new_d)
			new_numwords++;
	if (new_numwords == 0)
		return (NULL);
	new_s = malloc((1 + new_numwords) * sizeof(char *));
	if (!new_s)
		return (NULL);
	for (new_i = 0, new_j = 0; new_j < new_numwords; new_j++)
	{
		while (new_str[new_i] == new_d && new_str[new_i] != new_d)
			new_i++;
		new_k = 0;
		while (new_str[new_i + new_k] != new_d && new_str[new_i + new_k] && new_str[new_i + new_k] != new_d)
			new_k++;
		new_s[new_j] = malloc((new_k + 1) * sizeof(char));
		if (!new_s[new_j])
		{
			for (new_k = 0; new_k < new_j; new_k++)
				free(new_s[new_k]);
			free(new_s);
			return (NULL);
		}
		for (new_m = 0; new_m < new_k; new_m++)
			new_s[new_j][new_m] = new_str[new_i++];
		new_s[new_j][new_m] = 0;
	}
	new_s[new_j] = NULL;
	return (new_s);
}

