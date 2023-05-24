/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:34:08 by mat               #+#    #+#             */
/*   Updated: 2023/05/24 02:14:53 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	close_parent(t_command *cmd_data)
{
	if (g_global.cmd_nbr > 1 && cmd_data != NULL)
	{
		if (cmd_data->index > 1)
			close(cmd_data->prev_pipe);
		if (cmd_data->index == g_global.cmd_nbr)
			close(cmd_data->pipe_fds[0]);
	}
}
