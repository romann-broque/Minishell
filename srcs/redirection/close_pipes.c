/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:34:08 by mat               #+#    #+#             */
/*   Updated: 2023/05/25 11:04:54 by rbroque          ###   ########.fr       */
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
