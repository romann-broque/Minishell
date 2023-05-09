/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/09 14:20:52 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	dup_files(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

static void	revert_dup_files(int in, int out)
{
	dup2(STDIN_FILENO, in);
	dup2(STDOUT_FILENO, out);
}

void	execution(t_command *cmd_data)
{
	char	*path;

	printf("in->%d\nout->%d\n\n", cmd_data->fdin, cmd_data->fdout);
	dup_files(cmd_data->fdin, cmd_data->fdout);
	if (is_builtin(cmd_data) == true)
		exec_builtin(cmd_data);
	else
	{
		path = get_path(cmd_data);
		add_deallocator(path, free);
		exec_binary(cmd_data, path);
	}
	revert_dup_files(cmd_data->fdin, cmd_data->fdout);
}
