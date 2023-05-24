#include "shell.h"

/**
 * clear_info - clear the fields the Info_t struct.
 * @info: Pointer to the Info_t struct.
 *
 * Description: This function initializes the fields of the Info_t struct
 * to their default values.
 */
void clear_info(Info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Sets the Info_t struct.
 * @info: Pointer to the Info_t struct.
 * @av: Argument vector.
 *
 * Description: This function sets the fields of the Info_t struct
 * based on the provided arguments.
 */
void set_info(Info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees the fields of the Info_t struct.
 * @info: Pointer to the Info_t struct.
 * @all: Flag indicating whether to free all fields.
 *
 * Description: This function frees the dynamically allocated fields
 * of the Info_t struct based on the provided flag.
 */
void free_info(Info_t *info, int all)
{
	if (info->argv)
	{
		ffree(info->argv);
		info->argv = NULL;
	}
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
		{
			free(info->arg);
			info->arg = NULL;
		}
		if (info->env)
		{
			free_list(&(info->env));
			info->env = NULL;
		}
		if (info->history)
		{
			free_list(&(info->history));
			info->history = NULL;
		}
		if (info->alias)
		{
			free_list(&(info->alias));
			info->alias = NULL;
		}
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
		{
			close(info->readfd);
		}
		_putchar(BUF_FLUSH);
	}
}

