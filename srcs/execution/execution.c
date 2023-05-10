/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/10 15:13:07 by rbroque          ###   ########.fr       */
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

static void	dup_files(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	execution(t_command *cmd_data)
{
	char	*path;

	if (cmd_data->fdin != -1 && cmd_data->fdout != -1)
	{
		dup_files(cmd_data->fdin, cmd_data->fdout);
		if (is_builtin(cmd_data) == true)
			exec_builtin(cmd_data);
		else
		{
			path = get_path(cmd_data);
			add_deallocator(path, free);
			exec_binary(cmd_data, path);
		}
		dup_files(g_global.stdin, g_global.stdout);
	}
	if (cmd_data->fdin != STDIN_FILENO)
		close(cmd_data->fdin);
	if (cmd_data->fdout != STDOUT_FILENO)
		close(cmd_data->fdout);
	if (g_global.heredoc == true)
		unlink(HDOC_TMP_FILE);
}
