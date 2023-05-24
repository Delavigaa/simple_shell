#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @h: a reference to the first node
 *
 * Return: 	list's length
 */
size_t list_len(const list_t *h)
{
    size_t new_i = 0;

    while (h)
    {
    h = h->next;
    new_i++;
    }
    return (new_i);
}

/**
 * list_to_strings - returns a list of strings using the list->str method
 * @head: the initial node's pointer
 *
 * Return: several strings
 */
char **list_to_strings(list_t *head)
{
    list_t *new_node = head;
    size_t new_i = list_len(head), new_j;
    char **new_strs;
    char *new_str;

    if (!head || !new_i)
    return (NULL);
    new_strs = malloc(sizeof(char *) * (new_i + 1));
    if (!new_strs)
    return (NULL);
    for (new_i = 0; new_node; new_node = new_node->next, new_i++)
    {
    new_str = malloc(_strlen(new_node->str) + 1);
    if (!new_str)
    {
    for (new_j = 0; new_j < new_i; new_j++)
    free(new_strs[new_j]);
    free(new_strs);
    return (NULL);
    }

    new_str = _strcpy(new_str, new_node->str);
    new_strs[new_i] = new_str;
    }
    new_strs[new_i] = NULL;
    return (new_strs);
}


/**
 * print_list - displays all of a list_t linked list's components
 * @h:  the initial node's pointer
 *
 * Return: list's length
 */
size_t print_list(const list_t *h)
{
    size_t new_i = 0;

    while (h)
    {
    _puts(convert_number(h->num, 10, 0));
    _putchar(':');
    _putchar(' ');
    _puts(h->str ? h->str : "(nil)");
    _puts("\n");
    h = h->next;
    new_i++;
    }
    return (new_i);
}

/**
 * node_starts_with - brings back the node whose string has a prefix
 * @new_node: the list head as the cursor
 * @new_prefix: string matching
 * @new_c: the character that follows the prefix that matches
 *
 * Return: the appropriate node or NULL
 */
list_t *node_starts_with(list_t *new_node, char *new_prefix, char new_c)
{
    char *new_p = NULL;

    while (new_node)
    {
    new_p = starts_with(new_node->str, new_prefix);
    if (new_p && ((new_c == -1) || (*new_p == new_c)))
    return (new_node);
    new_node = new_node->next;
    }
    return (NULL);
}

/**
 * get_node_index - retrieves a node's index
 * @new_head: the list head as the cursor
 * @new_node: reference to the node
 *
 * Return: the node's index, or -1
 */
ssize_t get_node_index(list_t *new_head, list_t *new_node)
{
    size_t new_i = 0;

    while (new_head)
    {
    if (new_head == new_node)
    return (new_i);
    new_head = new_head->next;
    new_i++;
    }
    return (-1);
}

