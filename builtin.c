#include "shell.h"

/**
 * custom_myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int custom_myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = error_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			puts(info->argv[1]);
			putchar('\n');
			return (1);
		}
		info->err_num = error_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * custom_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getenv(info, "OLDPWD="))
		{
			puts(s);
			putchar('\n');
			return (1);
		}
		puts(getenv(info, "OLDPWD=")), putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		puts(info->argv[1]), putchar('\n');
	}
	else
	{
		setenv(info, "OLDPWD", getenv(info, "PWD="));
		setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
