/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:29:03 by mat               #+#    #+#             */
/*   Updated: 2023/05/15 00:40:21 by rbroque          ###   ########.fr       */
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

static void	signal_manag_child(const int status)
{
	if (WIFSIGNALED(status) == true)
	{
		if (WTERMSIG(status) == SIGINT)
		{
			printf("update global\n");
			update_global();
		}
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
}

void	exec_binary(t_command *cmd_data, char *path)
{
	int	status;

	if (path != NULL)
	{
		g_global.child_pid = fork();
		if (g_global.child_pid == 0)
		{
			update_signal_state(S_EXEC);
			child_job(cmd_data, path);
		}
		else if (g_global.child_pid > 0)
		{
			wait(&status);
			g_global.last_ret_val = extract_return_status(status);
			signal_manag_child(status);
		}
	}
}
