/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:54:40 by mat               #+#    #+#             */
/*   Updated: 2023/05/15 00:40:18 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	have_killable_child(void)
{
	return (g_global.child_pid != 0);
}

static void	handle_sigint(__attribute__((unused)) int signal)
{
	printf(NEWLINE_STR);
	rl_on_new_line();
	rl_replace_line(EMPTY_STR, 0);
	rl_redisplay();
	g_global.is_stoppable = true;
}

static void	handle_sigquit(__attribute__((unused)) int signal)
{
	if (have_killable_child() == true)
		update_global();
	else
	{
		rl_on_new_line();
		rl_replace_line(EMPTY_STR, 0);
		rl_redisplay();
	}
}

static void	set_default_catcher(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	update_signal_state(const t_sigstate state)
{
	if (state == S_EXEC)
		signal(SIGQUIT, handle_sigquit);
	else
		set_default_catcher();
}
