/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:27:39 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/28 13:05:54 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error_path(t_command *cmd_data, char **path)
{
	if (*path == NULL)
	{
		update_error_val(NO_FILE);
		if (is_var_path_in_env(cmd_data->env, PATH_VAR) == true)
			print_error("%s: %s: %s\n", MINISHELL, cmd_data->command[0], CNF);
		else
			print_error("%s: %s: %s\n", MINISHELL,
				cmd_data->command[0], NO_SUCH_FILE);
	}
	else if (is_cmd_accessible(*path) == false)
	{
		update_error_val(NO_ACCESS);
		print_error("%s: %s: %s", MINISHELL, *path, strerror(errno));
		free(*path);
		*path = NULL;
	}
}

char	*get_path(t_command *cmd_data)
{
	char	*path;

	if (is_cmd_path(cmd_data) == true)
		path = get_cmd_path(cmd_data);
	else
	{
		path = get_path_from_env(cmd_data->command[0],
				PATH_VAR, cmd_data->env);
		handle_error_path(cmd_data, &path);
	}
	return (path);
}

bool	is_executable_cmd(t_command *cmd)
{
	return (cmd->fdin != INVALID_FD
		&& cmd->fdout != INVALID_FD
		&& cmd->command != NULL);
}
