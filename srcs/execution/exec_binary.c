/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:29:03 by mat               #+#    #+#             */
/*   Updated: 2023/05/15 18:19:37 by mdorr            ###   ########.fr       */
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

//static void	dup_child(t_command *cmd_data)
//{
//	if (cmd_data->index == 1 && g_global.cmd_nbr > 1)
//		dup_files(cmd_data->fdin, g_global.pipes[1]);
//	else if (cmd_data->index == g_global.cmd_nbr && g_global.cmd_nbr > 1)
//		dup_files(g_global.pipes[0], cmd_data->fdout);
//	else if (g_global.cmd_nbr > 1)
//		dup_files(g_global.pipes[0], g_global.pipes[1]);
//}

static void	child_job(t_command *cmd_data, char *path)
{
	dup_files(cmd_data->fdin, cmd_data->fdout);
	printf("in child fdin is %d, fdout is %d", cmd_data->fdin, cmd_data->fdout);
	close_pipes_child(cmd_data);
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

void	exec_binary(t_command *cmd_data, char *path)
{
	int	pid;
	int	status;

	if (path != NULL)
	{

		pid = fork();
		if (pid == 0)
			child_job(cmd_data, path);
		else if (pid > 0)
		{
			wait(&status);
			close_pipes_parent(cmd_data);
			g_global.last_ret_val = extract_return_status(status);
		}
	}
}
