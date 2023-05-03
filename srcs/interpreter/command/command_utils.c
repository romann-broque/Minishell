/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:42:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 15:24:56 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(t_list *tokens, t_list *env)
{
	t_command	*cmd_data;

	cmd_data = (t_command *)malloc(sizeof(t_command));
	if (cmd_data != NULL)
	{
		cmd_data->command = get_arg_array(tokens);
		if (cmd_data->command == NULL)
			return (NULL);
		cmd_data->env = dup_env_lst_to_array(env);
		cmd_data->fdin = STDIN_FILENO;
		cmd_data->fdout = STDOUT_FILENO;
	}
	return (cmd_data);
}

// NOTES
//For the MVE with redirections and PIPES :
//		We will have to pass into argument of init_command the type of the token
//		following the command so that we know which fdin and fdout to set.

void	free_command(t_command *cmd_data)
{
	if (cmd_data != NULL)
	{
		free_strs(cmd_data->command);
		free_strs(cmd_data->env);
	}
	free(cmd_data);
}
