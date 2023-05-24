/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:16:33 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/24 02:19:35 by rbroque          ###   ########.fr       */
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

static t_command	*get_cmd_from_index(t_list *cmd_lst, const size_t index)
{
	size_t	i;

	i = 0;
	while (cmd_lst != NULL && i < index)
	{
		++i;
		cmd_lst = cmd_lst->next;
	}
	if (cmd_lst != NULL)
		return (cmd_lst->content);
	return (NULL);
}

void	wait_for_exec(t_list *cmd_lst)
{
	int		status;
	pid_t	pid;
	size_t	pid_index;
	size_t	i;

	i = 0;
	while (i < g_global.cmd_nbr)
	{
		pid = wait(&status);
		pid_index = get_index_from_pid(pid);
		close_parent(get_cmd_from_index(cmd_lst, pid_index));
		if (pid_index + 1 == g_global.cmd_nbr)
			g_global.last_ret_val = WEXITSTATUS(status);
		++i;
	}
}
