/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:42:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/05 10:45:28 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_assign_from_var(t_var *var)
{
	char *const	assign = ft_strjoin(var->key, EQUAL_SIGN_STR);

	return (ft_strjoin_free(assign, var->value));
}

char	**dup_env_lst_to_array(t_list *env_lst)
{
	return (dup_env_lst_to_array_gen(env_lst, ENV_MASK, get_assign_from_var));
}

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
