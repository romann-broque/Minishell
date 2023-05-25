/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:16:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/25 11:04:59 by rbroque          ###   ########.fr       */
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

static t_command	*get_cmd_from_index(const size_t index)
{
	t_list	*cmd_lst;
	size_t	i;

	cmd_lst = g_global.cmd_lst;
	i = 0;
	while (cmd_lst != NULL && i < index)
	{
		++i;
		cmd_lst = cmd_lst->next;
	}
	if (cmd_lst == NULL)
		return (NULL);
	return (cmd_lst->content);
}

static void	process_waiting(int *status)
{
	const pid_t	pid = wait(status);
	size_t		pid_index;
	t_command	*cmd;

	pid_index = get_index_from_pid(pid);
	if (pid_index + 1 == g_global.cmd_nbr)
		g_global.last_ret_val = WEXITSTATUS(*status);
	cmd = get_cmd_from_index(pid_index);
	close_parent(cmd);
}

void	wait_for_exec(void)
{
	int		status;
	bool	is_sigprinted;
	size_t	i;

	is_sigprinted = false;
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
