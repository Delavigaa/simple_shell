#include "shell.h"

/**
 * add_node - adds a node to the list's beginning
 * @head: address of the reference to the head node
 * @str: node's string field
 * @num: History makes use of a node index
 *
 * Return: a reference to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - inserts a node at the end of the list
 * @head: address of the reference to the head node
 * @str: the string component of the node
 * @num: using history's node index
 *
 * Return: pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_end_node, *current_node;

	if (!head)
		return (NULL);

	current_node = *head;
	new_end_node = malloc(sizeof(list_t));
	if (!new_end_node)
		return (NULL);
	_memset((void *)new_end_node, 0, sizeof(list_t));
	new_end_node->num = num;
	if (str)
	{
		new_end_node->str = _strdup(str);
		if (!new_end_node->str)
		{
			free(new_end_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_end_node;
	}
	else
		*head = new_end_node;
	return (new_end_node);
}

/**
 * print_list_str - only outputs a list_t linked list's string element
 * @current_node: identifier for the root node
 *
 * Return: size of the list's nodes
 */
size_t print_list_str(const list_t *current_node)
{
	size_t i = 0;

	while (current_node)
	{
		_puts(current_node->str ? current_node->str : "(nil)");
		_puts("\n");
		current_node = current_node->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - eliminates the node at the specified index
 * @head: the initial node's address for the pointer
 * @index: the node to delete's indexindex of the deleted nod
 *
 * Return: index of the deleted nod 1 for success and 0 for failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current_node, *previous_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *head;
	while (current_node)
	{
		if (i == index)
		{
			previous_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		i++;
		previous_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 * free_list - removes all nodes from a list
 * @head_ptr: Location of the head node's pointer
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *current_node, *next_current_node, *current_head;

	if (!head_ptr || !*head_ptr)
		return;
	current_head = *head_ptr;
	current_node = current_head;
	while (current_node)
	{
		next_current_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_current_node;
	}
	*head_ptr = NULL;
}

