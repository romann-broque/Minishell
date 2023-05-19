/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:54:40 by mat               #+#    #+#             */
/*   Updated: 2023/05/19 14:54:35 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	set_inter_catcher(void)
{
	signal(SIGINT, handle_sigint_inter);
	signal(SIGQUIT, SIG_IGN);
}

void	update_signal_state(const t_sigstate state)
{
	if (state == S_EXEC)
	{
		signal(SIGINT, clear_line_handler);
		signal(SIGQUIT, clear_line_handler);
	}
	else if (state == S_INTER)
		set_inter_catcher();
	else if (state == S_SLEEP)
		set_sleep_catcher();
	else
		set_default_catcher();
}
