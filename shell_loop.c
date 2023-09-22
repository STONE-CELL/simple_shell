#include "shell.h"

/**
 * hsh - Entry point
 * @info: input
 * @av: input
 *
 * Return: 0 on success, 1 on error.
 */
int hsh(info_t *info, char **av)
{
	ssize_t s = 0;
	int t = 0;

	while (s != -1 && t != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, av);
			t = find_builtin(info);
			if (t == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (t == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (t);
}

/**
 * find_builtin - Entry point
 * @info:input
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int o, t = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (o = 0; builtintbl[o].type; o++)
		if (_strcmp(info->argv[0], builtintbl[o].type) == 0)
		{
			info->line_count++;
			t = builtintbl[o].func(info);
			break;
		}
	return (t);
}

/**
 * find_cmd - Entry point
 * @info: input
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *p = NULL;
	int o, u;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (o = 0, u = 0; info->arg[o]; o++)
		if (!is_delim(info->arg[o], " \t\n"))
			u++;
	if (!u)
		return;

	p = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->path = p;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Entry point
 * @info: input
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t d;

	d = fork();
	if (d == -1)
	{
		perror("Error:");
		return;
	}
	if (d == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

