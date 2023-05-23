/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/23 17:04:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	execute(t_command *cmd_data)
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

static void	execute_cmd(t_command *cmd_data)
{
	if (is_executable_cmd(cmd_data) == true)
	{
		if (g_global.cmd_nbr == 1)
			dup_files(cmd_data);
		execute(cmd_data);
		if (g_global.cmd_nbr == 1)
			revert_dup(cmd_data);
	}
	else
		g_global.last_ret_val = (cmd_data->fdin == INVALID_FD
				|| cmd_data->fdout == INVALID_FD);
}

void	execution(t_command *cmd_data)
{
	int	status;
	int	pid;

	if (g_global.cmd_nbr == 1)
		execute_cmd(cmd_data);
	else
	{
		pipe(cmd_data->pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			dup_child(cmd_data);
			execute_cmd(cmd_data);
			exit_shell(g_global.last_ret_val, false);
		}
		else
		{
			waitpid(pid, &status, 0);
			g_global.last_ret_val = extract_return_status(status);
			close_parent(cmd_data);
			g_global.prev_pipe = cmd_data->pipe_fds[0];
		}
	}
}
