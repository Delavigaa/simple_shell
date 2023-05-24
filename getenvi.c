#include "shell.h"

/**
 * get_environ - Retrieves a copy of the environment strings array
 * @info: Pointer to the Info_t structure
 *
 * Return: The environment strings array
 */
char **get_environ(Info_t *info)
{
	if (!info->environ || info->env_modified)
	{
		info->environ = list_to_strings(info->env);
		info->env_modified = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes an environment variable
 * @info: Pointer to the Info_t structure
 * @var: The environment variable to be removed
 *
 * Return: 1 on success, 0 otherwise
 */
int _unsetenv(Info_t *info, char *var)
{
	list_t *current_node = info->env;
	size_t index = 0;
	char *prefix;

	if (!current_node || !var)
		return (0);

	while (current_node)
	{
		prefix = starts_with(current_node->str, var);
		if (prefix && *prefix == '=')
		{
			info->env_modified = delete_node_at_index(&(info->env), index);
			index = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		index++;
	}
	return (info->env_modified);
}

/**
 * _setenv - Sets or modifies an environment variable
 * @info: Pointer to the Info_t structure
 * @var: The environment variable to be set or modified
 * @value: The value to be assigned to the environment variable
 *
 * Return: 0 on success, 1 on failure
 */
int _setenv(Info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *current_node;
	char *prefix;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	current_node = info->env;
	while (current_node)
	{
		prefix = starts_with(current_node->str, var);
		if (prefix && *prefix == '=')
		{
			free(current_node->str);
			current_node->str = buffer;
			info->env_modified = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_modified = 1 ;
	return (0);
	}

