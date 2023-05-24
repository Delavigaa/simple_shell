#include "shell.h"

/**
 * hsh - general shell loop
 * @info: information struct for parameters and returns
 * @new_av: the main ()function's parameter vector
 *
 * Return: 1 for errors, 0 for successes, or an error code
 */
int hsh(Info_t *info, char **new_av)
{
	ssize_t read_result = 0;
	int builtin_ret = 0;

	while (read_result != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_result = get_input(info);
		if (read_result != -1)
		{
			set_info(info, new_av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - identifies a built-in command
 * @info: information struct for parameters and returns
 *
 * Return: -1 if a built-in cannot be discovered
 * 	0 if the builtin was properly run,
 * 	if a built-in is detected but not used,
 * 	If built-in signals are 2, exit()
 */
int find_builtin(Info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
			{"env", _myenv},
			{"help", _myhelp},
			{"history", _myhistory},
			{"setenv", _mysetenv},
			{"unsetenv", _myunsetenv},
			{"cd", _mycd},
			{"alias", _myalias},
			{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - search for a command in PATH
 * @info: information struct for parameters and returns
 *
 * Return: 1_void
 */
void find_cmd(Info_t *info)
{
	char *path = NULL;
	int i, count_non_delim = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, count_non_delim = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			count_non_delim++;
	if (!count_non_delim)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - creates an exec thread to execute cmd
 * @info: the argument and return information struct
 *
 * Return: 2_void
 */
void fork_cmd(Info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

