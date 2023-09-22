#include "shell.h"

/**
 * _myexit - Entry point
 * @info:input
 * Return:(0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int e;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		e = _erratoi(info->argv[1]);
		if (e == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Entry point
 * @info:input
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *y, *r, b[1024];
	int t;

	y = getcwd(b, 1024);
	if (!y)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		r = _getenv(info, "HOME=");
		if (!r)
			t = /* TODO: what should this be? */
				chdir((r = _getenv(info, "PWD=")) ? r : "/");
		else
			t = chdir(r);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(y);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		t = /* TODO: what should this be? */
			chdir((r = _getenv(info, "OLDPWD=")) ? r : "/");
	}
	else
		t = chdir(info->argv[1]);
	if (t == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(b, 1024));
	}
	return (0);
}

/**
 * _myhelp - Entry point
 * @info: input
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **y;

	y = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*y); /* temp att_unused workaround */
	return (0);
}

