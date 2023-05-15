/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:54:40 by mat               #+#    #+#             */
/*   Updated: 2023/05/15 11:21:06 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_line_handler(__attribute__((unused)) int signal)
{
	clear_line();
}

static void	handle_sigint_default(__attribute__((unused)) int signal)
{
	printf(NEWLINE_STR);
	clear_line();
}

static void	set_default_catcher(void)
{
	signal(SIGINT, handle_sigint_default);
	signal(SIGQUIT, SIG_IGN);
}

static void	set_sleep_catcher(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	update_signal_state(const t_sigstate state)
{
	if (state == S_EXEC)
	{
		signal(SIGINT, clear_line_handler);
		signal(SIGQUIT, clear_line_handler);
	}
	else if (state == S_SLEEP)
		set_sleep_catcher();
	else
		set_default_catcher();
}
