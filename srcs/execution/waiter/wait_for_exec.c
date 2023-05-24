/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:16:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/24 17:37:58 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static size_t	get_index_from_pid(const pid_t pid)
{
	const unsigned long	pid_nb = pid;
	t_list				*pid_lst;
	size_t				index;

	index = 0;
	pid_lst = g_global.pid_lst;
	while (pid_lst != NULL)
	{
		if (pid_lst->content == (void *)pid_nb)
			break ;
		++index;
		pid_lst = pid_lst->next;
	}
	return (index);
}

static void	process_waiting(int *status)
{
	const pid_t	pid = wait(status);
	size_t		pid_index;

	pid_index = get_index_from_pid(pid);
	if (pid_index + 1 == g_global.cmd_nbr)
		g_global.last_ret_val = WEXITSTATUS(*status);
}

void	wait_for_exec(void)
{
	int		status;
	bool	is_sigprinted;
	size_t	i;

	is_sigprinted = false;
	close_pipe_fds();
	i = 0;
	while (i < g_global.cmd_nbr)
	{
		process_waiting(&status);
		if (WIFSIGNALED(status) && is_sigprinted == false)
		{
			print_child_signal(status);
			is_sigprinted = true;
		}
		++i;
	}
}
