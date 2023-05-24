/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/24 16:00:00 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	execute(t_command *cmd_data)
{
	int		ret_val;
	char	*path;

	ret_val = EXIT_SUCCESS;
	if (is_builtin(cmd_data) == true)
		ret_val = exec_builtin(cmd_data);
	else
	{
		path = get_path(cmd_data);
		add_deallocator(path, free);
		if (g_global.cmd_nbr == 1)
			ret_val = exec_binary(cmd_data, path);
		else
		{
			if (path != NULL)
				child_job(cmd_data, path);
			ret_val = g_global.last_ret_val;
		}
	}
	return (ret_val);
}

static int	execute_cmd(t_command *cmd_data)
{
	int	ret_val;

	if (is_executable_cmd(cmd_data) == true)
	{
		dup_files(cmd_data);
		close_pipe_fds();
		ret_val = execute(cmd_data);
		revert_dup(cmd_data);
	}
	else
		ret_val = (cmd_data->fdin == INVALID_FD
				|| cmd_data->fdout == INVALID_FD);
	return (ret_val);
}

void	execution(t_command *cmd_data)
{
	int	pid;

	if (g_global.cmd_nbr == 1)
		g_global.last_ret_val = execute_cmd(cmd_data);
	else
	{
		pid = fork();
		if (pid == 0)
			exit_shell(execute_cmd(cmd_data), false);
		else
			ft_lstadd_back(&(g_global.pid_lst), ft_lstnew((void *)(long)(pid)));
	}
}
