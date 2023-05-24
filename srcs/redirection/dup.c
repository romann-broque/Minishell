/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:37 by mat               #+#    #+#             */
/*   Updated: 2023/05/24 23:53:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	dup_infile(t_command *cmd_data)
{
	if (cmd_data->fdin == STDIN_FILENO)
	{
		if (cmd_data->index > 0)
			cmd_data->fdin = cmd_data->prev_pipe;
	}
}

static void	dup_outfile(t_command *cmd_data)
{
	if (cmd_data->fdout == STDOUT_FILENO)
	{
		if (cmd_data->index + 1 < g_global.cmd_nbr)
			cmd_data->fdout = cmd_data->pipe_fds[1];
	}
}

void	dup_child(t_command *cmd_data)
{
	if (g_global.cmd_nbr > 1)
	{
		dup_infile(cmd_data);
		dup_outfile(cmd_data);
	}
}

void	dup_files(t_command *cmd_data)
{
	if (cmd_data->fdin != STDIN_FILENO)
		dup2(cmd_data->fdin, STDIN_FILENO);
	if (cmd_data->fdout != STDOUT_FILENO)
		dup2(cmd_data->fdout, STDOUT_FILENO);
	if (cmd_data->fderr != STDERR_FILENO)
		dup2(cmd_data->fderr, STDERR_FILENO);
}

void	revert_dup(t_command *cmd_data)
{
	if (cmd_data->fdin != STDIN_FILENO)
		dup2(g_global.stdin, STDIN_FILENO);
	if (cmd_data->fdout != STDOUT_FILENO)
		dup2(g_global.stdout, STDOUT_FILENO);
	if (cmd_data->fderr != STDERR_FILENO)
		dup2(g_global.stderr, STDERR_FILENO);
}
