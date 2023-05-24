#include "shell.h"

/**
 * input_buf - Reads input from the user and processes it.
 * @info: Pointer to the Info_t struct.
 * @buf: Double pointer to the input buffer.
 * @len: Pointer to the size of the buffer.
 *
 * Return: Number of bytes read.
 */
ssize_t input_buf(Info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = _getline(info, buf, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = bytes_read;
			info->cmd_buf = buf;
		}
	}
	return (bytes_read);
}

/**
 * get_input - Gets user input and processes it.
 * @info: Pointer to the Info_t struct.
 *
 * Return: Number of bytes read.
 */
ssize_t get_input(Info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &buf, &len);
	if (bytes_read == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (bytes_read);
}

/**
 * read_buf - Reads data from the read file descriptor into the buffer.
 * @info: Pointer to the Info_t struct.
 * @buf: Buffer to store the read data.
 * @i: Pointer to the current position in the buffer.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(Info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*i = bytes_read;
	return (bytes_read);
}

/**
 * _getline - Reads a line of input from the user.
 * @info: Pointer to the Info_t struct.
 * @ptr: Double pointer to the input buffer.
 * @length: Pointer to the length of the buffer.
 *
 * Return: Number of bytes read.
 */
int _getline(Info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, total_bytes = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		total_bytes = *length;
	if (i == len)
		i = len = 0;

	bytes_read = read_buf(info, buf, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, total_bytes, total_bytes ? total_bytes + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (total_bytes)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	total_bytes += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = total_bytes;
	*ptr = p;
	return (total_bytes);
}

/**
 * sigintHandler - Signal handler for SIGINT.
 * @sig_num: Signal number.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

