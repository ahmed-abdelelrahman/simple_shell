#include "shell.h"

/**
 * my_print_env - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int my_print_env(info_t *info)
{
	print_list_string(info->env);
	return (0);
}

/**
 * get_env_value - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: the value of the environment variable or NULL if not found
 */
char *get_env_value(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_set_env - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int my_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		puts("Incorrect number of arguments\n");
		return (1);
	}
	if (set_environment_variable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *            constant function prototype.
 * Return: Always 0
 */
int my_unset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i < info->argc; i++)
		unset_environment_variable(info, info->argv[i]);

	return (0);
}

/**
 * initialize_env_list - populates env linked list with the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 * Return: Always 0
 */
int initialize_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * starts_with - checks if a string starts with a prefix
 * @str: the string to check
 * @prefix: the prefix to look for
 *
 * Return: pointer to the location of prefix within str, or NULL if not found
 */
char *starts_with(const char *str, const char *prefix)
{
	size_t i;

	for (i = 0; prefix[i]; i++)
	{
		if (str[i] != prefix[i])
			return (NULL);
	}

	return ((char *)str + i);
}
