#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: struct information
 * @new_path: Head to the file
 *
 * Return: 0 if false, 1 if true
 */
int is_cmd(Info_t *info, char *new_path)
{
	struct stat st;

	(void)info;
	if (!new_path || stat(new_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - character duplication
 * @new_pathstr: PATH is a string
 * @start: beginning index
 * @stop: halting index
 *
 * Return: identifier for the fresh buffer
 */
char *dup_chars(char *new_pathstr, int start, int stop)
{
	static char new_buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (new_pathstr[i] != ':')
			new_buf[k++] = new_pathstr[i];
	new_buf[k] = 0;
	return (new_buf);
}

/**
 * find_path - the command is located in the PATH string
 * @info: struct information
 * @new_pathstr: the string PATH
 * @new_cmd: the direction to look
 *
 * Return: if the command is detected, its complete path; else, NULL
 */
char *find_path(Info_t *info, char *new_pathstr, char *new_cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!new_pathstr)
		return (NULL);
	if ((_strlen(new_cmd) > 2) && starts_with(new_cmd, "./"))
	{
		if (is_cmd(info, new_cmd))
			return (new_cmd);
	}
	while (1)
	{
		if (!new_pathstr[i] || new_pathstr[i] == ':')
		{
			path = dup_chars(new_pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, new_cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, new_cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!new_pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

