/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:54:40 by mat               #+#    #+#             */
/*   Updated: 2023/04/21 13:45:44 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	handle_sigint(__attribute__((unused)) int signal)
{
	printf("\n");
	if (g_global.is_stoppable == true && g_global.child_pid != 0)
	{
		kill(g_global.child_pid, SIGINT);
		update_global();
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}	

void	set_catcher(void)
{
	signal(SIGINT, handle_sigint);
}
