/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:29:03 by mat               #+#    #+#             */
/*   Updated: 2023/05/01 11:32:11 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

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
		g_global.last_ret_val = NO_ACCESS;
		print_error("%s: %s: %s\n", MINISHELL, path, IS_DIR);
		free_manager();
		exit(g_global.last_ret_val);
	}
	else if (execve(path, cmd_data->command, cmd_data->env) == -1)
		exit(g_global.last_ret_val);
}

void	exec_binary(t_command *cmd_data, char *path)
{
	int	pid;
	int	status;

	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
			child_job(cmd_data, path);
		else if (pid > 0)
		{
			wait(&status);
			g_global.last_ret_val = extract_return_status(status);
		}
	}
}
