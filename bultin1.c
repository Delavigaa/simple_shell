#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line, preceded
 *              with line numbers starting at 0.
 * @info: Pointer to the Info_t struct
 *
 * Return: Always 0
 */
int _myhistory(Info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias
 * @info: Pointer to the Info_t struct
 * @str: The alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(Info_t *info, char *str)
{
	char *equal_sign, saved_char;
	int ret;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return (1);
	saved_char = *equal_sign;
	*equal_sign = '\0';
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equal_sign = saved_char;
	return (ret);
}

/**
 * set_alias - Sets an alias
 * @info: Pointer to the Info_t struct
 * @str: The alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(Info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return (1);
	if (!*++equal_sign)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string
 * @node: Pointer to the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *equal_sign_pos = NULL, *current_char = NULL;

	if (node)
	{
		equal_sign_pos = _strchr(node->str, '=');
		for (current_char = node->str; current_char <= equal_sign_pos; current_char++)
			_putchar(*current_char);
		_putchar('\'');
		_puts(equal_sign_pos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias builtin (man alias)
 * @info: Pointer to the Info_t struct
 *
 * Return: Always 0
 */
int _myalias(Info_t *info)
{
	int i = 0;
	char *equal_sign_pos = NULL;
	list_t *current_node = NULL;

	if (info->argc == 1)
	{
		current_node = info->alias;
		while (current_node)
		{
			print_alias(current_node);
			current_node = current_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_pos = _strchr(info->argv[i], '=');
		if (equal_sign_pos)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

