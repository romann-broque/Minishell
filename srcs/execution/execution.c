/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/22 11:33:55 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	handle_error_path(t_command *cmd_data, char **path)
{
	if (*path == NULL)
	{
		update_error_val(NO_FILE);
		print_error("%s: %s: ", MINISHELL, cmd_data->command[0]);
		if (is_var_path_in_env(cmd_data->env, PATH_VAR) == true)
			print_error("%s\n", CNF);
		else
			print_error("%s\n", NO_SUCH_FILE);
	}
	else if (is_cmd_accessible(*path) == false)
	{
		update_error_val(NO_ACCESS);
		print_error("%s: %s: ", MINISHELL, *path);
		perror(EMPTY_STR);
		free(*path);
		*path = NULL;
	}
}

static char	*get_path(t_command *cmd_data)
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

static bool	is_executable_cmd(t_command *cmd)
{
	return (cmd->fdin != INVALID_FD
		&& cmd->fdout != INVALID_FD
		&& cmd->command != NULL);
}

void	execution(t_command *cmd_data)
{
	char	*path;

	if (is_executable_cmd(cmd_data) == true)
	{
		if (is_builtin(cmd_data) == true)
			exec_builtin(cmd_data);
		else
		{
			path = get_path(cmd_data);
			add_deallocator(path, free);
			exec_binary(cmd_data, path);
		}
	}
}
