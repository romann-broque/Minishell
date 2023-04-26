/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:31:24 by mat               #+#    #+#             */
/*   Updated: 2023/04/26 15:53:37 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	init_global(void)
{
	init_tracker();
	g_global.is_stoppable = true;
	g_global.child_pid = 0;
}

bool	is_child_dead(void)
{
	char *const	char_pid = ft_itoa(g_global.child_pid);
	char *const	proc_path = ft_strjoin("/proc/", char_pid);
	struct stat	sts;
	bool		ret_val;

	ret_val = (stat(proc_path, &sts) == -1 && errno == ENOENT);
	free(char_pid);
	free(proc_path);
	return (ret_val);
}

void	update_global(void)
{
	if (g_global.is_stoppable == true && is_child_dead() == true)
	{
		g_global.is_stoppable = false;
		g_global.child_pid = 0;
	}
}
