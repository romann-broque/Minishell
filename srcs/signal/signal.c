/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:54:40 by mat               #+#    #+#             */
/*   Updated: 2023/04/21 14:25:05 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	have_killable_child(void)
{
	return (g_global.is_stoppable == true && g_global.child_pid != 0);
}

static void	handle_sigint(__attribute__((unused)) int signal)
{
	printf(NEWLINE_STR);
	if (have_killable_child() == true)
	{
		kill(g_global.child_pid, SIGINT);
		update_global();
	}
	else
	{
		rl_on_new_line();
		rl_replace_line(EMPTY_STR, 0);
		rl_redisplay();
	}
}	

void	set_catcher(void)
{
	signal(SIGINT, handle_sigint);
}
