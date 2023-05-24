#include "shell.h"

/**
 * get_history_file - brings up the history file
 * @info: element struct
 *
 * Return: allocated string holding the path to the history file
 */

char *get_history_file(Info_t *info)
{
	char *new_buf, *new_dir;

	new_dir = _getenv(info, "HOME=");
	if (!new_dir)
		return (NULL);
	new_buf = malloc(sizeof(char) * (_strlen(new_dir) + _strlen(HIST_FILE) + 2));
	if (!new_buf)
		return (NULL);
	new_buf[0] = 0;
	_strcpy(new_buf, new_dir);
	_strcat(new_buf, "/");
	_strcat(new_buf, HIST_FILE);
	return (new_buf);
}

/**
 * write_history - adds a new file or a new section to an existing one
 * @info: the struct of parameters
 *
 * Return: If you succeed you get a 1  if you fail you get a -1
 */
int write_history(Info_t *info)
{
	ssize_t new_fd;
	char *new_filename = get_history_file(info);
	list_t *new_node = NULL;

	if (!new_filename)
		return (-1);

	new_fd = open(new_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(new_filename);
	if (new_fd == -1)
		return (-1);
	for (new_node = info->history; new_node; new_node = new_node->next)
	{
		_putsfd(new_node->str, new_fd);
		_putfd('\n', new_fd);
	}
	_putfd(BUF_FLUSH, new_fd);
	close(new_fd);
	return (1);
}

/**
 * read_history - examines a file's history
 * @info: the struct of parameterst
 *
 * Return: if successful, histcount; if not, 0
 */
int read_history(Info_t *info)
{
	int new_i, new_last = 0, new_linecount = 0;
	ssize_t new_fd, new_rdlen, new_fsize = 0;
	struct stat new_st;
	char *new_buf = NULL, *new_filename = get_history_file(info);

	if (!new_filename)
		return (0);

	new_fd = open(new_filename, O_RDONLY);
	free(new_filename);
	if (new_fd == -1)
		return (0);
	if (!fstat(new_fd, &new_st))
		new_fsize = new_st.st_size;
	if (new_fsize < 2)
		return (0);
	new_buf = malloc(sizeof(char) * (new_fsize + 1));
	if (!new_buf)
		return (0);
	new_rdlen = read(new_fd, new_buf, new_fsize);
	new_buf[new_fsize] = 0;
	if (new_rdlen <= 0)
		return (free(new_buf), 0);
	close(new_fd);
	for (new_i = 0; new_i < new_fsize; new_i++)
		if (new_buf[new_i] == '\n')
		{
			new_buf[new_i] = 0;
			build_history_list(info, new_buf + new_last, new_linecount++);
			new_last = new_i + 1;
		}
	if (new_last != new_i)
		build_history_list(info, new_buf + new_last, new_linecount++);
	free(new_buf);
	info->histcount = new_linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - includes a new entry in the history linked list
 * @info: Potential argument-containing structure. employed to keep
 * @new_buf: buffer
 * @new_linecount: the number of lines in history (histcount)
 *
 * Return: Always zero
 */
int build_history_list(Info_t *info, char *new_buf, int new_linecount)
{
	list_t *new_node = NULL;

	if (info->history)
		new_node = info->history;
	add_node_end(&new_node, new_buf, new_linecount);

	if (!info->history)
		info->history = new_node;
	return (0);
}

/**
 * renumber_history - Following updates, renumbers the history linked list
 * @info: Structure with potential arguments. used to keep things running
 *
 * Return: the new count
 */
int renumber_history(Info_t *info)
{
	list_t *new_node = info->history;
	int new_i = 0;

	while (new_node)
	{
		new_node->num = new_i++;
		new_node = new_node->next;
	}
	return (info->histcount = new_i);
}

