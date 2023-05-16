/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:29:03 by mat               #+#    #+#             */
/*   Updated: 2023/05/16 15:47:42 by mdorr            ###   ########.fr       */
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

static void	dup_infile(t_command *cmd_data)
{
	if (cmd_data->fdin == STDIN_FILENO && g_global.cmd_nbr > 1)
	{
		if (cmd_data->index > 1)
			cmd_data->fdin = g_global.prev_pipe;
	}
	dup2(cmd_data->fdin, STDIN_FILENO);
}

static void	dup_outfile(t_command *cmd_data, int *end)
{
	if (cmd_data->fdout == STDOUT_FILENO && g_global.cmd_nbr > 1)
	{
		if (cmd_data->index < g_global.cmd_nbr)
			cmd_data->fdout = end[1];
	}
	dup2(cmd_data->fdout, STDOUT_FILENO);
}

static void	dup_child(t_command *cmd_data, int *end)
{
	dup_infile(cmd_data);
	dup_outfile(cmd_data, end);
}

static void	child_job(t_command *cmd_data, char *path, int *end)
{
	dup_child(cmd_data, end);
	close(end[1]);
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

static void	close_parent(int *end, t_command *cmd_data)
{
	if (g_global.cmd_nbr > 1)
	{
		if (cmd_data->index > 1)
			close(g_global.prev_pipe);
		close(end[1]);
	}
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
