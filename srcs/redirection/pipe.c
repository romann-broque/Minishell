/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:34:08 by mat               #+#    #+#             */
/*   Updated: 2023/05/25 11:19:08 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	close_parent(t_command *cmd_data)
{
	if (cmd_data != NULL)
	{
		close_safe(cmd_data->prev_pipe);
		close_safe(cmd_data->pipe_fds[1]);
		close_safe(cmd_data->pipe_fds[0]);
	}
}

void	close_pipe_fds(void)
{
	ft_lstiter(g_global.cmd_lst, (void (*)(void *))close_parent);
}

static void	assign_in_end(t_command *cmd_data)
{
	if (cmd_data->fdin == STDIN_FILENO)
	{
		if (cmd_data->index > 0)
			cmd_data->fdin = cmd_data->prev_pipe;
	}
}

static void	assign_out_end(t_command *cmd_data)
{
	if (cmd_data->fdout == STDOUT_FILENO)
	{
		if (cmd_data->index + 1 < g_global.cmd_nbr)
			cmd_data->fdout = cmd_data->pipe_fds[1];
	}
}

void	assign_end_pipe(t_command *cmd_data)
{
	if (g_global.cmd_nbr > 1)
	{
		assign_in_end(cmd_data);
		assign_out_end(cmd_data);
	}
}
