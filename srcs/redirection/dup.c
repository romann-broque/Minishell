/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:37 by mat               #+#    #+#             */
/*   Updated: 2023/05/17 11:51:07 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	dup_infile(t_command *cmd_data)
{
	if (cmd_data->fdin == STDIN_FILENO && g_global.cmd_nbr > 1)
	{
		if (cmd_data->index > 1)
			cmd_data->fdin = g_global.prev_pipe;
	}
	dup2(cmd_data->fdin, STDIN_FILENO);
}

void	dup_outfile(t_command *cmd_data, int *end)
{
	if (cmd_data->fdout == STDOUT_FILENO && g_global.cmd_nbr > 1)
	{
		if (cmd_data->index < g_global.cmd_nbr)
			cmd_data->fdout = end[1];
	}
	dup2(cmd_data->fdout, STDOUT_FILENO);
}

void	dup_child(t_command *cmd_data, int *end)
{
	dup_infile(cmd_data);
	dup_outfile(cmd_data, end);
}
