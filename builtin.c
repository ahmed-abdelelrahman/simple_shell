#include "shell.h"

/**
 * mina_robir_myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int mina_robir_myexit(inforobir_t *inforobir)
{
	int robir_exitcheck;

	if (inforobir->argv[1])  /* If there is an exit arguement */
	{
		robir_exitcheck = _erratoi(inforobir->argv[1]);
		if (robir_exitcheck == -1)
		{
			inforobir->status = 2;
			print_error(inforobir, "Illegal number: ");
			_eputs(inforobir->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inforobir->err_num = _erratoi(inforobir->argv[1]);
		return (-2);
	}
	inforobir->err_num = -1;
	return (-2);
}

/**
 * robir_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int robir_mycd(inforobir_t *inforobir)
{
	char *q, *directory, robir_buffer[1024];
	int chdirmena_ret;

	q = getcwd(robir_buffer, 1024);
	if (!q)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inforobir->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			chdirmena_ret = /* TODO: what should this be? */
				chdir((directory = _getenv(inforobir, "PWD=")) ? directory : "/");
		else
			chdirmena_ret = chdir(directory);
	}
	else if (_strcmp(inforobir->argv[1], "-") == 0)
	{
		if (!_getenv(inforobir, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inforobir, "OLDPWD=")), _putchar('\n');
		chdirmena_ret = /* TODO: what should this be? */
			chdir((directory = _getenv(inforobir, "OLDPWD=")) ? directory : "/");
	}
	else
		chdirmena_ret = chdir(inforobir->argv[1]);
	if (chdirmena_ret == -1)
	{
		print_error(inforobir, "can't cd to ");
		_eputs(inforobir->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inforobir, "OLDPWD", _getenv(inforobir, "PWD="));
		_setenv(inforobir, "PWD", getcwd(robir_buffer, 1024));
	}
	return (0);
}

/**
 * robir_myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int robir_myhelp(info_t *info)
{
	char **robir_arg_array;

	robir_arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*robir_arg_array); /* temp att_unused workaround */
	return (0);
}
