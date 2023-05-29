/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:31:37 by mat               #+#    #+#             */
/*   Updated: 2023/05/29 17:49:43 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	*g_global;

void	dup_files(t_command *cmd_data)
{
	if (cmd_data->fdin != STDIN_FILENO)
		dup2(cmd_data->fdin, STDIN_FILENO);
	if (cmd_data->fdout != STDOUT_FILENO)
		dup2(cmd_data->fdout, STDOUT_FILENO);
}

void	revert_dup(t_command *cmd_data)
{
	if (cmd_data->fdin != STDIN_FILENO)
		dup2(g_global->stdin, STDIN_FILENO);
	if (cmd_data->fdout != STDOUT_FILENO)
		dup2(g_global->stdout, STDOUT_FILENO);
}
