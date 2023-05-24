#ifndef _SHELL_H_
#define _SHELL_H_

#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

/* about convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2



/* reading/writing buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


/* 1 if system getline() is used */
#define USE_GETLINE 0
#define USE_STRTOK 0



/* for order to chain commands */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 * struct passinfo - comprises fictitious arguments that may be sent to a function,
 * enabling standardized prototype for function pointer struct
 * @arg: a string produced by getline that contains arguments
 * @argv:a collection of strings created from arg
 * @path: a string route for the active command
 * @argc: number of arguments
 * @line_count: the number of errors
 * @err_num: the exit ()s error code
 * @linecount_flag: if on count this input line
 * @fname: software's filename
 * @env: localized linked list copy of enviroment
 * @environ: LL env environment updated specifically
 * @history: historical node
 * @alias: an alias node
 * @env_modified: if the environment had altered
 * @status: the last command that was executed's return status
 * @cmd_buf: pointer to cmd_buf's address, if chaining
 * @cmd_buf_type: Command-type ||, &&, ;
 * @readfd: the fd to read line input from
 * @histcount: the amount of lines in history
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_modified;
	int status;

	char **cmd_buf; /* chain buffer; reference to cmd; for memory management */
	int cmd_buf_type; /* Command-type ||, &&, ; */
	int readfd;
	int histcount;
}
Info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}


/**
 * struct builtin - includes an integrated string and associated functions
 * @type: internal command flag
 * @func:  function
 */
typedef struct builtin
{
	char *type;
	int (*func)(Info_t *);
} builtin_table;

int is_chain(Info_t *, char *, size_t *);
void check_chain(Info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);
int replace_alias(Info_t *);
int replace_vars(Info_t *);


int hsh(Info_t *, char **);
void fork_cmd(Info_t *);
int find_builtin(Info_t *);
void find_cmd(Info_t *);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);

char *dup_chars(char *, int, int);
char *find_path(Info_t *, char *, char *);
int is_cmd(Info_t *, char *);

list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);
int delete_node_at_index(list_t **, unsigned int);


int loophsh(char **);


int _putfd(char c, int fd);
int _eputchar(char);
int _putsfd(char *str, int fd);
void _eputs(char *);

int _unsetenv(Info_t *, char *);
char **get_environ(Info_t *);
int _setenv(Info_t *, char *, char *);


int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);


char *_getenv(Info_t *, const char *);
int _myunsetenv(Info_t *);
int populate_env_list(Info_t *);
int _myenv(Info_t *);
int _mysetenv(Info_t *);



char *_strcpy(char *, char *);
int _putchar(char);
char *_strdup(const char *);
void _puts(char *);




void clear_info(Info_t *);
void free_info(Info_t *, int);
void set_info(Info_t *, char **);


char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);


ssize_t get_input(Info_t *);
void sigintHandler(int);
int _getline(Info_t *, char **, size_t *);


char **strtow2(char *, char);
char **strtow(char *, char *);


int _myalias(Info_t *);
int _myhistory(Info_t *);


char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);


int _myexit(Info_t *);
int _myhelp(Info_t *);
int _mycd(Info_t *);


int bfree(void **);


int _erratoi(char *);
char *convert_number(long int, int, int);
void print_error(Info_t *, char *);
int print_d(int, int);
void remove_comments(char *);


int interactive(Info_t *);
int _atoi(char *);
int is_delim(char, char *);
int _isalpha(int);

char *get_history_file(Info_t *info);
int write_history(Info_t *info);
int read_history(Info_t *info);
int build_history_list(Info_t *info, char *buf, int linecount);
int renumber_history(Info_t *info);

#endif

