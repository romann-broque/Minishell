/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:21:22 by mat               #+#    #+#             */
/*   Updated: 2023/05/11 15:46:00 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	init_pipe_and_command(t_list **cmd_lst, t_command *cmd)
{
	t_command *const	prev_cmd = ft_lstlast(*cmd_lst)->content;

	prev_cmd->fdout = g_global.pipes[1];
	cmd = init_command();
	cmd->fdin = g_global.pipes[0];
	ft_lstadd_back(cmd_lst, ft_lstnew(cmd));
}
