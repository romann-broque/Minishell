/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:34:08 by mat               #+#    #+#             */
/*   Updated: 2023/05/19 09:59:55 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	close_child(int *end)
{
	close(end[0]);
	close(end[1]);
	close(g_global.prev_pipe);
}

void	close_parent(int *end, t_command *cmd_data)
{
	close(end[1]);
	if (g_global.cmd_nbr > 1 && cmd_data->index > 1)
		close(g_global.prev_pipe);
	if (cmd_data->index == g_global.cmd_nbr)
		close(end[0]);
}
