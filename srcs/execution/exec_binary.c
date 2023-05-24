/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:29:03 by mat               #+#    #+#             */
/*   Updated: 2023/05/24 17:22:07 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	is_folder(const char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
	{
		perror(STAT_ERROR);
		exit_shell(EXIT_FAILURE, false);
	}
	return (S_ISDIR(file_stat.st_mode));
}

static void	child_job(t_command *cmd_data, char *path)
{
	if (is_folder(path) == true)
	{
		g_global.last_ret_val = NO_ACCESS;
		print_error("%s: %s: %s\n", MINISHELL, path, IS_DIR);
		exit_shell(g_global.last_ret_val, false);
	}
	update_signal_state(S_EXEC);
	execve(path, cmd_data->command, cmd_data->env);
	update_signal_state(S_SLEEP);
	exit_shell(g_global.last_ret_val, false);
}

int	exec_binary(t_command *cmd_data, char *path)
{
	int	status;
	int	pid;
	int	ret_val;

	ret_val = g_global.last_ret_val;
	if (path != NULL)
	{
		if (g_global.cmd_nbr == 1)
		{
			pid = fork();
			if (pid == 0)
				child_job(cmd_data, path);
			else if (pid > 0)
			{
				waitpid(pid, &status, WUNTRACED);
				ret_val = extract_return_status(status);
				print_child_signal(status);
			}
		}
		else
			child_job(cmd_data, path);
	}
	return (ret_val);
}
