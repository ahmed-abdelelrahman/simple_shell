#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = custom_strtow(info->arg, " \t"); // Your implementation of strtow
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = custom_strdup(info->arg); // Your implementation of _strdup
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        custom_replace_alias(info); // Your implementation of replace_alias
        custom_replace_vars(info); // Your implementation of replace_vars
    }
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
    custom_ffree(info->argv); // Your implementation of ffree
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            custom_free_list(&(info->env)); // Your implementation of free_list
        if (info->history)
            custom_free_list(&(info->history)); // Your implementation of free_list
        if (info->alias)
            custom_free_list(&(info->alias)); // Your implementation of free_list
        custom_ffree(info->environ); // Your implementation of ffree
        info->environ = NULL;
        custom_bfree((void **)info->cmd_buf); // Your implementation of bfree
        if (info->readfd > 2)
            close(info->readfd);
        custom_putchar(BUF_FLUSH); // Your implementation of _putchar
    }
}
