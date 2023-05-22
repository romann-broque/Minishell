/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:29:03 by mat               #+#    #+#             */
/*   Updated: 2023/05/22 11:16:21 by mat              ###   ########.fr       */
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
		free_manager();
		exit(EXIT_FAILURE);
	}
	return (S_ISDIR(file_stat.st_mode));
}

static void	child_job(t_command *cmd_data, char *path)
{
	dup_child(cmd_data);
	close_child(cmd_data->end);
	if (is_folder(path) == true)
	{
		g_global.last_ret_val = NO_ACCESS;
		print_error("%s: %s: %s\n", MINISHELL, path, IS_DIR);
		free_manager();
		exit(g_global.last_ret_val);
	}
	else if (execve(path, cmd_data->command, cmd_data->env) == -1)
		exit(g_global.last_ret_val);
}

static void	print_child_signal(const int status)
{
	if (WIFSIGNALED(status) == true)
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_printf(QUIT_CDUMP);
		ft_printf(NEWLINE_STR);
	}
}

void	exec_binary(t_command *cmd_data, char *path)
{
	int	status;
	int	pid;

	pipe(cmd_data->end);
	if (path != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			update_signal_state(S_EXEC);
			child_job(cmd_data, path);
		}
		else if (pid > 0)
		{
			wait(&status);
			close_parent(cmd_data);
			g_global.last_ret_val = extract_return_status(status);
			g_global.prev_pipe = cmd_data->end[0];
			print_child_signal(status);
		}
	}
}
