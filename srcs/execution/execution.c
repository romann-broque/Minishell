/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/22 16:46:13 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_folder(const char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
	{
		perror(STAT_ERROR);
		free_manager();
		exit(EXIT_FAILURE);
	}
	return (S_ISDIR(file_stat.st_mode));
}

static void	child_job(t_command *cmd_data, char *path)
{
	if (is_folder(path) == true)
	{
		print_error("%s: %s: %s\n", MINISHELL, path, IS_DIR);
		free_manager();
		exit(EXIT_FAILURE);
	}
	else if (execve(path, cmd_data->command, cmd_data->env) == -1)
		exit(EXIT_FAILURE);
}

static void	exec_binary(t_command *cmd_data, char *path)
{
	int	pid;

	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
			child_job(cmd_data, path);
		else if (pid > 0)
			wait(NULL);
	}
}

static char	*get_path(t_command *cmd_data)
{
	char	*path;

	if (is_cmd_path(cmd_data) == true)
	{
		path = get_path_from_cmd(cmd_data);
		if (path == NULL)
		{
			print_error("%s: %s: ", MINISHELL, cmd_data->command[0]);
			perror(EMPTY_STR);
		}
	}
	else
	{
		path = get_path_from_env(cmd_data);
		if (path == NULL)
			print_error("%s: %s\n", cmd_data->command[0], CMD_NOT_FOUND);
	}
	return (path);
}

void	execution(t_command *cmd_data)
{
	char	*path;

	if (is_builtin(cmd_data) == true)
		exec_builtin(cmd_data);
	else
	{
		path = get_path(cmd_data);
		add_deallocator(path, free);
		exec_binary(cmd_data, path);
	}
}
