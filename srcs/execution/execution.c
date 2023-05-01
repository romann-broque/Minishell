/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/01 14:22:26 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_command *cmd_data)
{
	char	*path;

	if (is_cmd_path(cmd_data) == true)
		path = get_cmd_path(cmd_data);
	else
	{
		path = get_path_from_env(cmd_data->command[0],
				PATH_VAR, cmd_data->env);
		if (path == NULL)
		{
			update_error_val(NO_FILE);
			print_error("%s: %s: %s\n", MINISHELL, cmd_data->command[0], CNF);
		}
		else if (is_cmd_accessible(path) == false)
		{
			update_error_val(NO_ACCESS);
			print_error("%s: %s: ", MINISHELL, path);
			perror(EMPTY_STR);
			free(path);
			path = NULL;
		}
	}
	return (path);
}

void	execution(t_command *cmd_data)
{
	char	*path;

	if (is_builtin(cmd_data) == true)
		exec_builtin(cmd_data);
	else
	{
		path = get_path(cmd_data);
		add_deallocator(path, free);
		exec_binary(cmd_data, path);
	}
}
