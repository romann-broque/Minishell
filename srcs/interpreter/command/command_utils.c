/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:42:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/16 15:05:36 by mdorr            ###   ########.fr       */
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
		g_global.cmd_nbr++;
		cmd_data->index = g_global.cmd_nbr;
		cmd_data->command = NULL;
		cmd_data->env = NULL;
		cmd_data->fdin = STDIN_FILENO;
		cmd_data->fdout = STDOUT_FILENO;
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
	}
	free(cmd_data);
}
