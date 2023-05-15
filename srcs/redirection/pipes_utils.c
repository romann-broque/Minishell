/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:21:22 by mat               #+#    #+#             */
/*   Updated: 2023/05/15 18:20:57 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	close_pipes_parent(t_command *cmd_data)
{
	if (cmd_data->index == 1 && g_global.cmd_nbr > 1)
		close(g_global.pipes[1]);
	else if (cmd_data->index == g_global.cmd_nbr && g_global.cmd_nbr > 1)
		close(g_global.pipes[0]);
	else
	{
		close(g_global.pipes[0]);
		close(g_global.pipes[1]);
	}
}

void	close_pipes_child(t_command *cmd_data)
{
	if (cmd_data->index == 1 && g_global.cmd_nbr > 1)
		close(g_global.pipes[0]);
	else if (cmd_data->index == g_global.cmd_nbr && g_global.cmd_nbr > 1)
		close(g_global.pipes[1]);
	else// if (g_global.cmd_nbr == 1)
	{
		close(g_global.pipes[1]);
		close(g_global.pipes[0]);
	}
}


void	init_pipe_and_command(t_list **cmd_lst, t_command *cmd)
{
	t_command *const	prev_cmd = ft_lstlast(*cmd_lst)->content;

	prev_cmd->fdout = g_global.pipes[1];
	cmd = init_command();
	cmd->fdin = g_global.pipes[0];
	ft_lstadd_back(cmd_lst, ft_lstnew(cmd));
}
