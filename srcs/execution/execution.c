/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/15 19:18:11 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_folder(const char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
	{
		perror("Failed to stat file");
		exit(EXIT_FAILURE);
	}
	return (S_ISDIR(file_stat.st_mode));
}

static void	exec_binary(t_command *cmd_data, char *path)
{
	int	pid;

	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (is_folder(path) == true)
			{
				print_error("%s: %s: Is a directory\n", MINISHELL, path);
				free_manager();
				exit(EXIT_FAILURE);
			}
			else
				exit(execve(path, cmd_data->command, cmd_data->env) == -1);
		}
		else if (pid > 0)
			wait(NULL);
	}
}

void	execution(t_command *cmd_data)
{
	char	*path;

	if (is_builtin(cmd_data) == true)
		exec_builtin(cmd_data);
	else
	{
		if (is_cmd_path(cmd_data) == true)
		{
			path = get_path_from_cmd(cmd_data);
			if (path == NULL)
				perror(MINISHELL);
		}
		else
		{
			path = get_path_from_env(cmd_data);
			if (path == NULL)
				print_error("%s: %s\n", cmd_data->command[0], CMD_NOT_FOUND);
		}
		add_deallocator(path, free);
		exec_binary(cmd_data, path);
	}
}
