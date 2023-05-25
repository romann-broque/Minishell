/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:42:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/25 20:04:31 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static char	*get_assign_from_var(t_var *var)
{
	char *const	assign = ft_strjoin(var->key, EQUAL_SIGN_STR);

	return (ft_strjoin_free(assign, var->value));
}

char	**dup_env_lst_to_array(t_list *env_lst)
{
	return (get_env_array(env_lst, ENV_MASK, get_assign_from_var));
}

t_command	*init_command(void)
{
	t_command	*cmd_data;

	cmd_data = (t_command *)malloc(sizeof(t_command));
	if (cmd_data != NULL)
	{
		cmd_data->index = g_global.cmd_index;
		cmd_data->command = NULL;
		cmd_data->env = NULL;
		cmd_data->fdin = STDIN_FILENO;
		cmd_data->fdout = STDOUT_FILENO;
		cmd_data->fderr = dup(STDERR_FILENO);
		cmd_data->pipe_fds[0] = INVALID_FD;
		cmd_data->pipe_fds[1] = INVALID_FD;
		cmd_data->prev_pipe = g_global.prev_pipe;
	}
	return (cmd_data);
}

void	free_command(t_command *cmd_data)
{
	if (cmd_data != NULL)
	{
		free_strs(cmd_data->command);
		free_strs(cmd_data->env);
		if (cmd_data->fdin != STDIN_FILENO)
			close(cmd_data->fdin);
		if (cmd_data->fdout != STDOUT_FILENO)
			close(cmd_data->fdout);
		if (cmd_data->fderr != STDERR_FILENO)
			close(cmd_data->fderr);
		close_parent(cmd_data);
	}
	free(cmd_data);
}
