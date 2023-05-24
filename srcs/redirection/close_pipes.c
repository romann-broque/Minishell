/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:34:08 by mat               #+#    #+#             */
/*   Updated: 2023/05/24 12:34:58 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	close_parent(t_command *cmd_data)
{
	if (g_global.cmd_nbr > 1 && cmd_data != NULL)
	{
		if (cmd_data->index > 0)
		{
			close(cmd_data->prev_pipe);
			close(cmd_data->pipe_fds[1]);
		}
		if (cmd_data->index + 1 == g_global.cmd_nbr)
			close(cmd_data->pipe_fds[0]);
	}
}
