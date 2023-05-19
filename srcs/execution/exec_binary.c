/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:29:03 by mat               #+#    #+#             */
/*   Updated: 2023/05/17 11:52:07 by mat              ###   ########.fr       */
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

static void	child_job(t_command *cmd_data, char *path, int *end)
{
	dup_child(cmd_data, end);
	close_child(end);
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
	int	end[2];
	int	pid;
	int	status;

	pipe(end);
	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
			child_job(cmd_data, path, end);
		else if (pid > 0)
		{
			wait(&status);
			close_parent(end, cmd_data);
			g_global.last_ret_val = extract_return_status(status);
			g_global.prev_pipe = end[0];
		}
	}
}
