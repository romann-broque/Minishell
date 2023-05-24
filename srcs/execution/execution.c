/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:52:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/24 02:19:39 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	execute(t_command *cmd_data)
{
	int		ret_val;
	char	*path;

	if (is_builtin(cmd_data) == true)
		ret_val = exec_builtin(cmd_data);
	else
	{
		path = get_path(cmd_data);
		add_deallocator(path, free);
		ret_val = exec_binary(cmd_data, path);
	}
	return (ret_val);
}

static int	execute_cmd(t_command *cmd_data)
{
	int	ret_val;

	if (is_executable_cmd(cmd_data) == true)
	{
		if (g_global.cmd_nbr == 1)
			dup_files(cmd_data);
		ret_val = execute(cmd_data);
		if (g_global.cmd_nbr == 1)
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
		{
			dup_child(cmd_data);
			exit_shell(execute_cmd(cmd_data), false);
		}
		else
			ft_lstadd_back(&(g_global.pid_lst), ft_lstnew((void *)(long)(pid)));
	}
}
