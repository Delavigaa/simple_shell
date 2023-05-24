#include "shell.h"

/**
 * is_chain - determines if the currently-in-the-buffer character is a chain delimiter.
 * @new_info: the struct of parameters
 * @new_buf: character buffer
 * @new_p: address for the present job in BUF
 *
 * Return: If the chain delimiter is present, the value is 1, otherwise it is 0.
 */
int is_chain(Info_t *new_info, char *new_buf, size_t *new_p)
{
	size_t new_j = *new_p;

	if (new_buf[new_j] == '|' && new_buf[new_j + 1] == '|')
	{
		new_buf[new_j] = 0;
		new_j++;
		new_info->cmd_buf_type = CMD_OR;
	}
	else if (new_buf[new_j] == '&' && new_buf[new_j + 1] == '&')
	{
		new_buf[new_j] = 0;
		new_j++;
		new_info->cmd_buf_type = CMD_AND;
	}
	else if (new_buf[new_j] == ';') /* found the end of this command */
	{
		new_buf[new_j] = 0; /* replace semicolon with null */
		new_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*new_p = new_j;
	return (1);
}

/**
 * check_chain - determines whether to continue chaining depending on the most recent status.
 * @new_info: struct for the argument
 * @new_buf: character buffer
 * @new_p: address for the present job in BUF
 * @new_i: beginning place in buf
 * @new_len: size of buf
 *
 * Return: 1_Void.
 */
void check_chain(Info_t *new_info, char *new_buf, size_t *new_p, size_t new_i, size_t new_len)
{
	size_t new_j = *new_p;

	if (new_info->cmd_buf_type == CMD_AND)
	{
		if (new_info->status)
		{
			new_buf[new_i] = 0;
			new_j = new_len;
		}
	}
	if (new_info->cmd_buf_type == CMD_OR)
	{
		if (!new_info->status)
		{
			new_buf[new_i] = 0;
			new_j = new_len;
		}
	}

	*new_p = new_j;
}

/**
 * replace_alias - substitutes a tokenized string's alias.
 * @new_info: struct for the argument
 *
 * Return: 0 otherwise, 1 if replaced
 */
int replace_alias(Info_t *new_info)
{
	int new_i;
	list_t *new_node;
	char *new_p;

	for (new_i = 0; new_i < 10; new_i++)
	{
		new_node = node_starts_with(new_info->alias, new_info->argv[0], '=');
		if (!new_node)
			return (0);
		free(new_info->argv[0]);
		new_p = _strchr(new_node->str, '=');
		if (!new_p)
			return (0);
		new_p = _strdup(new_p + 1);
		if (!new_p)
			return (0);
		new_info->argv[0] = new_p;
	}
	return (1);
}

/**
 * replace_vars - replacing the tokenized string's variables with replacements
 * @new_info: struct for the argument
 *
 * Return: 0 otherwise, 1 if replaced
 */
int replace_vars(Info_t *new_info)
{
	int new_i = 0;
	list_t *new_node;

	for (new_i = 0; new_info->argv[new_i]; new_i++)
	{
		if (new_info->argv[new_i][0] != '$' || !new_info->argv[new_i][1])
			continue;

		if (!_strcmp(new_info->argv[new_i], "$?"))
		{
			replace_string(&(new_info->argv[new_i]),
					_strdup(convert_number(new_info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(new_info->argv[new_i], "$$"))
		{
			replace_string(&(new_info->argv[new_i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		new_node = node_starts_with(new_info->env, &new_info->argv[new_i][1], '=');
		if (new_node)
		{
			replace_string(&(new_info->argv[new_i]),
					_strdup(_strchr(new_node->str, '=') + 1));
			continue;
		}
		replace_string(&new_info->argv[new_i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - changes a string
 * @new_old: location of the previous string
 * @new_new: fresh string
 *
 * Return: 0 otherwise, 1 if replaced
 */
int replace_string(char **new_old, char *new_new)
{
	free(*new_old);
	*new_old = new_new;
	return (1);
}

