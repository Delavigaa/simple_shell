#include "shell.h"

/**
 * main - access point
 * @new_ac: count the arguments
 * @new_av: vector arg
 *
 * Return: 0 for success, 1 for failure
 */
int main(int new_ac, char **new_av)
{
	Info_t new_info[] = { INFO_INIT };
	int new_fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (new_fd)
			: "r" (new_fd));

	if (new_ac == 2)
	{
		new_fd = open(new_av[1], O_RDONLY);
		if (new_fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(new_av[0]);
				_eputs(": 0: Can't open ");
				_eputs(new_av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		new_info->readfd = new_fd;
	}
	populate_env_list(new_info);
	read_history(new_info);
	hsh(new_info, new_av);
	return (EXIT_SUCCESS);
}

